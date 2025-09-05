# ------------------------------------------------------------------------------
# Feature Engineering and Selection: Python version with pyreadr
# ------------------------------------------------------------------------------
import pyreadr
import pandas as pd
import numpy as np
from itertools import combinations
from sklearn.model_selection import RepeatedStratifiedKFold, cross_val_score
from sklearn.preprocessing import PowerTransformer, StandardScaler
from sklearn.linear_model import LogisticRegression
from sklearn.metrics import roc_auc_score, roc_curve, auc
import plotly.express as px
import pickle
from scipy.stats import ttest_rel
import matplotlib.pyplot as plt
import seaborn as sns

# ------------------------------------------------------------------------------
# Load the RData file
result = pyreadr.read_r("../../Data_Sets/Ischemic_Stroke/stroke_data.RData")
#print(result)
# result is a dictionary with object names as keys
stroke_train = result['stroke_train']
VC_preds = result['VC_preds']  # assuming it's a vector
risk_preds = result['risk_preds']  # assuming it's a vector

# Convert to list if necessary
VC_preds = VC_preds.iloc[:, 0].tolist()
risk_preds = risk_preds.iloc[:, 0].tolist()

# ------------------------------------------------------------------------------
# Function to compare two models using resampling
def compare_models_1way(model_a, model_b, Xa, Xb, y, metric='roc_auc'):
    cv = RepeatedStratifiedKFold(n_splits=10, n_repeats=5, random_state=42)
    scores_a = cross_val_score(model_a, Xa, y, cv=cv, scoring=metric)
    scores_b = cross_val_score(model_b, Xb, y, cv=cv, scoring=metric)
    #print("scores_a:", scores_a[:10])
    #print("scores_b:", scores_b[:10])
    diff_estimate = scores_a.mean() - scores_b.mean()
    t_stat, p_val = ttest_rel(scores_a, scores_b)
    return diff_estimate, p_val

# ------------------------------------------------------------------------------
# Null model (intercept only)
X_null = np.ones((stroke_train.shape[0], 1))
#print(type(X_null))
y = stroke_train['Stroke'].values
null_model = LogisticRegression(solver='liblinear')
null_model.fit(X_null, y)

# ------------------------------------------------------------------------------
all_preds = VC_preds + risk_preds
# Single predictor models
one_predictor_res = pd.DataFrame({
    'Predictor': all_preds,
    'Improvement': np.nan,
    'Pvalue': np.nan,
    'ROC': np.nan
})

for i, pred in enumerate(one_predictor_res['Predictor']):
    X_pred = stroke_train[[pred]].copy()
    pt = PowerTransformer(method='yeo-johnson')
    X_pred = pt.fit_transform(X_pred)
    #print(type(X_pred))
    #print(X_pred)
    #print("-----------")
    
    model = LogisticRegression(solver='liblinear')
    model.fit(X_pred, y)
    
    diff, p_val = compare_models_1way(model, null_model, X_pred, X_null, y)
    #print(diff, p_val)
    one_predictor_res.loc[i, 'ROC'] = roc_auc_score(y, model.predict_proba(X_pred)[:,1])
    one_predictor_res.loc[i, 'Improvement'] = diff
    one_predictor_res.loc[i, 'Pvalue'] = p_val

one_predictor_res_risk = one_predictor_res[one_predictor_res['Predictor'].isin(risk_preds)].sort_values('Pvalue')
#print(one_predictor_res_risk)

# ------------------------------------------------------------------------------
# Figure 2.4
vc_data = stroke_train[['Stroke'] + VC_preds].copy()
pt = PowerTransformer(method='yeo-johnson')
vc_data[VC_preds] = pt.fit_transform(vc_data[VC_preds])

vc_long = vc_data.melt(id_vars='Stroke', var_name='Predictor', value_name='value')

pred_max = vc_long.groupby('Predictor')['value'].max().reset_index()
pred_max = pred_max.merge(one_predictor_res[['Predictor','Pvalue']], on='Predictor')
pred_max['label'] = pred_max['Pvalue'].apply(lambda x: f"p-value: {x:.4f}")

sns.set(style="whitegrid")
predictors = vc_long['Predictor'].unique()

chunk_size = 9  # 每页9个子图（3x3）
for start in range(0, len(predictors), chunk_size):
    end = start + chunk_size
    subset = predictors[start:end]
    
    n_cols = 3
    n_rows = int(np.ceil(len(subset)/n_cols))
    
    fig, axes = plt.subplots(n_rows, n_cols, figsize=(4*n_cols, 3*n_rows))
    axes = axes.flatten()
    
    for i, predictor in enumerate(subset):
        ax = axes[i]
        data = vc_long[vc_long['Predictor'] == predictor]
        sns.boxplot(x='Stroke', y='value', data=data, ax=ax, hue="Stroke", palette="Set2")
        sns.stripplot(x='Stroke', y='value', data=data, ax=ax, color='gray', alpha=0.3, size=4)

        max_val = pred_max[pred_max['Predictor']==predictor]['value'].values[0]
        label = pred_max[pred_max['Predictor']==predictor]['label'].values[0]
        ax.text(1.5, 1.25*max_val, label, fontsize=10)
        ax.set_title(predictor)
        ax.set_xlabel('')
        ax.set_ylabel('')
    
    # 删除多余子图
    for j in range(i+1, n_rows*n_cols):
        fig.delaxes(axes[j])
    
    plt.tight_layout()
    #plt.show()

# ------------------------------------------------------------------------------
# Figure 2.5 ROC curve
#print(stroke_train['MaxRemodelingRatio'].nunique())
#print(stroke_train['Stroke'])
fpr, tpr, thresholds = roc_curve(stroke_train['Stroke'].map({'N': 0, 'Y': 1}), stroke_train['MaxRemodelingRatio'], drop_intermediate=False)
#print(len(fpr))
#print(tpr)
#print(thresholds)
roc_auc = auc(fpr, tpr)

fig_2_5=plt.figure(figsize=(6, 6))
plt.plot(fpr, tpr, color="darkorange", lw=2, label=f"ROC curve (AUC = {roc_auc:.2f})")
plt.plot([0, 1], [0, 1], color="navy", lw=2, linestyle="--")  # 对角线参考

plt.xlim([0.0, 1.0])
plt.ylim([0.0, 1.05])
plt.xlabel("False Positive Rate")
plt.ylabel("True Positive Rate")
plt.title("Receiver Operating Characteristic")
plt.legend(loc="lower right")
plt.grid(True)

# ------------------------------------------------------------------------------
# Interaction exploration
pairs = pd.DataFrame(list(combinations(VC_preds, 2)), columns=['V1', 'V2'])
pairs['Improvement'] = np.nan
pairs['Pvalue'] = np.nan
pairs['ROC'] = np.nan

scaler = StandardScaler()
for i, row in pairs.iterrows():
    X_pair = stroke_train[[row['V1'], row['V2']]].copy()
    X_pair_scaled = scaler.fit_transform(X_pair)
    
    # Main effects model
    main_model = LogisticRegression(solver='liblinear')
    main_model.fit(X_pair_scaled, y)
    
    # Interaction model
    X_interact = X_pair.copy()
    X_interact[f'{row["V1"]}_x_{row["V2"]}'] = X_pair[row['V1']] * X_pair[row['V2']]
    X_interact_scaled = scaler.fit_transform(X_interact)
    interact_model = LogisticRegression(solver='liblinear')
    interact_model.fit(X_interact_scaled, y)
    
    diff, p_val = compare_models_1way(interact_model, main_model, X_interact_scaled, X_pair_scaled, y)
    pairs.loc[i, 'ROC'] = roc_auc_score(y, main_model.predict_proba(X_pair_scaled)[:,1])
    pairs.loc[i, 'Improvement'] = diff
    pairs.loc[i, 'Pvalue'] = p_val

retained_pairs = pairs[(pairs['ROC'] > 0.5) & (pairs['Pvalue'] <= 0.2)]

# ------------------------------------------------------------------------------
## Figure 2.6 interactive plot
df_plot = pairs[pairs['ROC'] > 0.5].copy()  # filtered DataFrame
print(df_plot)

# Compute hover text and -log10(p-value) on the filtered DataFrame
df_plot['hover_text'] = df_plot.apply(
    lambda r: f"{r['V1']} by {r['V2']}\nROC: {r['ROC']:.2f}", axis=1
)
df_plot['minus_log10_p'] = -np.log10(df_plot['Pvalue'])
# 绘制散点图
fig_2_6, ax = plt.subplots(figsize=(6, 6))

scatter = ax.scatter(
    df_plot['Improvement'],
    df_plot['minus_log10_p'],
    s=df_plot['ROC'] * 200,   # 用 ROC (或者 baseline AUC，如果你有的话) 控制点大小
    c=df_plot['ROC'],         # 用 ROC 控制颜色
    cmap="viridis",
    alpha=0.7,
    edgecolor="k"
)

# 添加颜色条
cbar = plt.colorbar(scatter, ax=ax)
cbar.set_label("ROC")

# 标签
ax.set_xlabel("Improvement")
ax.set_ylabel("-log10(p)")
ax.set_title("Interactive-like Scatter Plot (ROC as size & color)")

plt.tight_layout()
plt.show()

#vol_plot = px.scatter(
#    df_plot,
#    x='Improvement',
#    y='minus_log10_p',
#    size='ROC',
#    hover_name='hover_text'
#)
#
#fig_2_4.show()
#fig_2_5.show()
#vol_plot.show()
## ------------------------------------------------------------------------------
## Save interaction formula
#interaction_terms = pairs[(pairs['ROC'] > 0.5) & (pairs['Pvalue'] <= 0.2) & (pairs['Improvement'] > 0)]
#int_form = '+'.join([f"{row['V1']}:{row['V2']}" for _, row in interaction_terms.iterrows()])
#
#with open('interactions.pkl', 'wb') as f:
#    pickle.dump(int_form, f)
