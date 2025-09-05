# ------------------------------------------------------------------------------
# Python translation of R preprocessing code (02_02_Preprocessing.R)
# Using pyreadr to load RData
# ------------------------------------------------------------------------------

import pyreadr
import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
import seaborn as sns
from sklearn.preprocessing import PowerTransformer, StandardScaler

# ------------------------------------------------------------------------------
# Load .RData file
result = pyreadr.read_r("../../Data_Sets/Ischemic_Stroke/stroke_data.RData")

# 查看 RData 文件中包含的对象
print("Objects in RData:", result.keys())

# 提取 R 的数据框
stroke_train = result["stroke_train"]
stroke_test = result["stroke_test"]

print("Train shape:", stroke_train.shape)
print("Test shape:", stroke_test.shape)

# ------------------------------------------------------------------------------
# Variable groups
VC_preds = [
    "CALCVol", "CALCVolProp", "MATXVol", "MATXVolProp", "LRNCVol",
    "LRNCVolProp", "MaxCALCArea", "MaxCALCAreaProp", "MaxDilationByArea",
    "MaxMATXArea", "MaxMATXAreaProp", "MaxLRNCArea", "MaxLRNCAreaProp",
    "MaxMaxWallThickness", "MaxRemodelingRatio", "MaxStenosisByArea",
    "MaxWallArea", "WallVol", "MaxStenosisByDiameter"
]

risk_preds = [
    "age", "sex", "SmokingHistory", "AtrialFibrillation", "CoronaryArteryDisease",
    "DiabetesHistory", "HypercholesterolemiaHistory", "HypertensionHistory"
]

# ------------------------------------------------------------------------------
# Count Stroke distribution in train and test
train_counts = stroke_train["Stroke"].value_counts().reset_index()
train_counts.columns = ["Stroke", "Count"]
train_counts["Data"] = "Training"

test_counts = stroke_test["Stroke"].value_counts().reset_index()
test_counts.columns = ["Stroke", "Count"]
test_counts["Data"] = "Testing"

stroke_counts = pd.concat([train_counts, test_counts], ignore_index=True)
print(stroke_counts.pivot(index="Data", columns="Stroke", values="Count"))

# ------------------------------------------------------------------------------
# Histogram before and after Yeo-Johnson transform

combined = pd.concat([stroke_train, stroke_test], ignore_index=True)

# (a) Raw histogram
plt.figure(figsize=(6,4))
sns.histplot(combined["MaxLRNCArea"], bins=15, color="#D53E4F", alpha=0.5)
plt.xlabel("MaxLRNCArea")
plt.ylabel("Frequency")
plt.title("(a)")
plt.savefig("dist_for_raw_MaxLRNCArea.png")

# (b) After Yeo-Johnson transformation
pt = PowerTransformer(method="yeo-johnson")
transformed = pt.fit_transform(combined[["MaxLRNCArea"]])

plt.figure(figsize=(6,4))
sns.histplot(transformed.flatten(), bins=15, color="#D53E4F", alpha=0.5)
plt.xlabel("Transformed MaxLRNCArea")
plt.ylabel("Frequency")
plt.title("(b)")
plt.savefig("dist_for_trans_MaxLRNCArea.png")

# ------------------------------------------------------------------------------
# Preprocessing risk_train: center, scale, Yeo-Johnson

risk_train = stroke_train[VC_preds].copy()

# Apply Yeo-Johnson + Standardization
pt = PowerTransformer(method="yeo-johnson")
scaler = StandardScaler()

risk_train_transformed = pt.fit_transform(risk_train)
risk_train_scaled = scaler.fit_transform(risk_train_transformed)

risk_train_final = pd.DataFrame(risk_train_scaled, columns=VC_preds)

# Drop Stroke, NASCET, and risk predictors (if they exist)
risk_train_final = risk_train_final.drop(
    columns=[c for c in ["Stroke", "NASCET"] + risk_preds if c in risk_train_final.columns],
    errors="ignore"
)

# ------------------------------------------------------------------------------
# Correlation matrix
risk_corr = risk_train_final.corr()

plt.figure(figsize=(12,10))
sns.heatmap(risk_corr, cmap="coolwarm", center=0, square=True)
plt.title("Correlation Matrix of Risk Variables")
plt.savefig("correlation_matrix_of_risk_variables.png")
