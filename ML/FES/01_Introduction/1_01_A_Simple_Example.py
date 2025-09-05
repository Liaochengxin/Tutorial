import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
import seaborn as sns

from sklearn.datasets import fetch_openml
from sklearn.linear_model import LogisticRegression
from sklearn.metrics import roc_curve, auc
from sklearn.preprocessing import PowerTransformer

from test import get_segmentation_data_from_r
# ---------------------------------------------------------------------
# Load segmentation dataset (from OpenML)
# We only keep two features + class + case info, as in the R example
# ---------------------------------------------------------------------
df = get_segmentation_data_from_r()
#print(df)

# Select the same variables as in the R code
df = df[["EqSphereAreaCh1", "PerimCh1", "Class", "Case"]].copy()
df.columns = ["PredictorA", "PredictorB", "Class", "Case"]


# Recode class: "PS" -> "One", otherwise "Two"
df["Class"] = np.where(df["Class"] == "PS", "One", "Two")

# Train/test split based on Case variable
train_df = df[df["Case"] == "Train"].drop(columns=["Case"])
test_df  = df[df["Case"] == "Test"].drop(columns=["Case"])

X_train = train_df[["PredictorA", "PredictorB"]].values
y_train = train_df["Class"].values

X_test = test_df[["PredictorA", "PredictorB"]].values
y_test = test_df["Class"].values

# ---------------------------------------------------------------------
# Logistic Regression on natural units
# ---------------------------------------------------------------------
clf_nat = LogisticRegression(max_iter=500)
clf_nat.fit(X_train, y_train)

# Predicted probabilities for the "One" class
y_score_nat = clf_nat.predict_proba(X_test)[:, 0]

# ROC curve + AUC
fpr_nat, tpr_nat, _ = roc_curve(y_test, y_score_nat, pos_label="One")
auc_nat = auc(fpr_nat, tpr_nat)

# Scatter plot (natural units)
plt.figure(figsize=(12,5))
plt.subplot(1,2,1)
sns.scatterplot(x="PredictorA", y="PredictorB", hue="Class", 
                data=train_df, alpha=0.5, s=40)
plt.title("(a) Natural Units")
plt.legend(loc="upper left")

# ---------------------------------------------------------------------
# Logistic Regression on Box-Cox transformed data
# ---------------------------------------------------------------------
pt = PowerTransformer(method="box-cox", standardize=True)

# Box-Cox requires strictly positive input -> add small shift
X_train_bc = pt.fit_transform(X_train + 1e-6)
print(type(X_train_bc))
X_test_bc  = pt.transform(X_test + 1e-6)

for i, lmbda in enumerate(pt.lambdas_):
    transform_type = "inverse" if np.isclose(lmbda, -1, atol=0.05) else "log" if np.isclose(lmbda, 0, atol=0.05) else "other"
    print(f"Column {i}: λ = {lmbda:.4f}, recommended transformation: {transform_type}")

clf_trans = LogisticRegression(max_iter=500)
clf_trans.fit(X_train_bc, y_train)

y_score_trans = clf_trans.predict_proba(X_test_bc)[:, 0]

# ROC curve + AUC
fpr_trans, tpr_trans, _ = roc_curve(y_test, y_score_trans, pos_label="One")
auc_trans = auc(fpr_trans, tpr_trans)

# Scatter plot (inverse representation)
plt.subplot(1,2,2)
sns.scatterplot(x=1/train_df["PredictorA"], y=1/train_df["PredictorB"], hue="Class",
                data=train_df, alpha=0.5, s=40)
plt.xlabel("1/A")
plt.ylabel("1/B")
plt.title("(a) Inverse Units")
plt.legend(loc="upper left")
plt.tight_layout()
plt.savefig("Original_Inverse_Units.png")
#plt.show()

# ---------------------------------------------------------------------
# ROC curve comparison between natural and transformed features
# ---------------------------------------------------------------------
plt.figure(figsize=(6,6))
plt.plot(fpr_nat, tpr_nat, label=f"Natural Units (AUC={auc_nat:.2f})", color="black")
plt.plot(fpr_trans, tpr_trans, label=f"Inverse Units (AUC={auc_trans:.2f})", color="blue")
plt.plot([0,1],[0,1], "k--", lw=1)

plt.xlabel("False Positive Rate")
plt.ylabel("True Positive Rate")
plt.title("(b) ROC Curve")
plt.legend(loc="lower right")
plt.savefig("ROC_Curve.png")
#plt.show()
