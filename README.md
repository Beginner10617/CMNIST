# CMNIST
A from scratch implementation of **MNIST digit classification in C.**

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
2. Intermediate Layer : 16 neurons, each taking 32 previous neuron activations as inputs
3. Output Layer : 10 neurons, each corresponding to each digit classification

Activation:
The first two layers have hyperbolic tangent (tanh) as the activation function, while the output layer has none

Loss: Sum of squared deviations of each sample in a batch are taken as loss. Apparently adding scaling based on batch size to implement "mean" squared error caused explosion in loss.

Current accuracy on the test sample is ~95.10%

---
## Implementation Details
**MNIST Parsing**
- Reads raw binary IDX format
- Performs manual endianness conversion
- Allocates memory dynamically for images and labels

**Autograd Engine**
Each `Value`node contains:
- `data`
- `grad`
- `_prev` (dependencies)
- `_backward` function pointer
- operation metadata
- `visited` flag for graph traversal
- `_isparameter` for handling memory allocation
  
Backward pass is performed by recursive graph traversal. 

Upon completion of a backward pass, memory allocated to non-paremeter value nodes that are generated during forward pass needs to be freed using `freeComputationTree()`

---
## Known Issues
- For large batch-size (~100) the loss function explodes
- Averaging loss function over a batch instead of adding leads to loss explosion as well
- Slow speed for large layers (originally intended MLP structure took hours on a training loop)

---
## Inspiration
- After watching [this video](https://youtu.be/JDoDWBpz7E8) by [bigboxSWE](https://youtube.com/@bigboxswe) I picked this project - usually implemented in python - and instead do it in C
- Andrej Karpathy's intro to neural networks [youtube video](https://youtu.be/VMj-3S1tku0)
