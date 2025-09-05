# 1.2 Importance Concepts

## overfitting

model have great performance in train sample, but can't predict new sample.
### Model bias and Variance
Models can also be evaluated in terms of variance and bias (Geman, Bienenstock, and Doursat [1992](http://www.feat.engineering/references#ref-geman1992neural))

**variance in model**: if a model have a small change in data but cause a sizable change in hyper parameters or structure.
- Low-variance model: linear regression, logistic regression, and partial least squares    
- High-variance model: classification or regression trees, nearest neighbor models, and neural networks 

**Bias in model**: Model bias reflects the ability of a model to conform to the underlying theoretical structure of the data.
- Low-Bias: can be highly flexible and has the capacity to fit a variety of different shapes and patterns 
- High-Bias: Unable to estimate value to their true theoretical counterparts 

**Variance-bias trade-off**

How to find low bias and low variance model: 

### Experience-Driven Modeling and Empirically Driven Modeling

Point: Data-Driven rather than experience-driven

Model have ability to find strong feature to maximize performance, danger here are 
- data-driven run the risk of overfitting to false patterns in data.
- highly complex model and no rational explanation

Combine data-driven and experience-driven

# 1.3 A More Complex Example

**Multicollinearity** : Linear model show worse result, after apply more feature, since it suffers high degree between variable correlation
**Note** : with appropriate feature, simple linear models can compare with complex model
![[Screenshot 2025-09-01 at 12.01.09.png]]
# 1.4 Feature Selection

Supervised feature selection: select feature based on correlation between input feature and target variable
![[Screenshot 2025-09-01 at 12.08.43.png]]
Unsupervised feature selection: select feature based on its own prepetry

**Note:**
- There may not be a unique set of predictors, many combination of features set can achieve similar performance.
- compensatory effect: one important variable is removed, the model adjusts using the remaining variable. Especially true for some degree of correlation between the explanatory variables or when a low-bias models is used.
- feature selection only can improve performance the model, rather be formal method to determine feature significance. (use inferential statistical approaches)