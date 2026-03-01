# CMNIST
A from scratch implementation of *MNIST digit classification in C.*

CMNIST is a minimal deep learning project that implements a Multi-Layer Perceptron (MLP), automatic differentiation, and training loop entirely in C - without using any external ML libraries.

---
## Features
- MNIST Dataset file parsing (`idx3-ubyte`, `idx1-ubyte`)
- Custom Value structure
- Reverse-mode automatic differentiation
- Multi-Layer Perception implementation
- Forward + Backward propagation
- SGD (Stochastic Gradient Descent) based training loop
---
## Model Description
The model consist of 3 simple layers:
1. Input Layer : 32 neurons, each with 784 inputs (28x28 flattened image data)
2. Intermediate Layer :
