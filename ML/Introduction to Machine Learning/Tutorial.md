# introduction

# Mathematical function 
## Core Definition
- Data: $(x_i, y_i)$, $x_i$ can be a vector which show the features, and $y_i$ is the label
- Model: Model actually is a function f, $y=f(x;\theta)$, $\theta$ is the parameter for function
- Loss function: a function to determine how well the function to predict data $x_i$, usually format are MSE(Mean-Squared error) and MAE(Mean-Absolute error). Example: $\frac{1}{N}\sum_i(y_i-f(x_i))^2$  or $\frac{1}{N}\sum_i|(y_i-f(x_i))|$ 
---
**Note:** likelihood and loss function
$$
L(x_1,x_2,..|\theta_1,\theta_2,...)=\frac{P(x_1,x_2,..)}{dx_1dx_2...}|_{\theta_1,\theta_2,..}
$$

--- 
## Gradient Descent
Parameter Update Strategy:
- Evaluate the gradient $\nabla_{\theta} L$, if it is negative which means point to $L(\theta)$ decreasing.
- update $\theta\rightarrow\theta-\alpha\nabla_{\theta} L$, $\alpha$ is known as learning rate 
---
**Note:** For Real neural network can have $O(10^4)$ parameters, but it cost lots of computational resources, a solution is to sample a small subset of points each time when gradient computed, this is know for batch gradient descent.

---

## Overfit
- Set training, validation, test set. tune parameter with validation set and apply model in test set.
- early stop: stop adjusting $\theta$ when loss function starts to show significant differ between training and validation set.

## regression, classification, generation
- regression: To predict a continuous function, a common loss function is MSE
- classification: class different types of sample, a common loss function is cross entropy
- generation: no idea!

# Neural Networks
## Theory introduction
Linear transformation: $y=Ax+b$, which A is a matrix and y and b have the same dimension, but x may have different dimension.

no-linear transformation: $f(x)=g(Ax+b)$, which g is known as activation function.![[Screenshot 2025-09-20 at 11.08.37.png]]
The display for neural network
![[Screenshot 2025-09-20 at 11.13.46.png]]

- vector x is referred to as input layer of network
- vector $g_{1}(A_{1}x+b_{1})$ is referred to hidden layers, and each element of vector is neuron
- the output vector is referred to output layer