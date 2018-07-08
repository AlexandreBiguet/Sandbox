# A tour of deep learning with CPP

[link to talk](https://www.youtube.com/watch?v=Lo1rXJdAJ7w)

## Notes 
 - Classification (supervised)
 - Generative. (unsupervised) 
 
 **Model Layer** 
 
 Generative Adversarial Networks (GAN) 2 components : a generator and a
 discriminator. The generator takes in input a vector of values. Produces bunch
 of data that looks like the input. The Discrinminator takes the output of the
 generator and computes a probability of (is real) for each component of the
 generator outputs. This probability is used a feedback in the generator. We
 want the probability high for the generator input and low for the generated
 outputs. This kind of technique is used to constructs e.g. faces
   
The discriminator is composed of several layers like convolutionnal layers, 
and stuff.

**Convolution Layer** 
Need input + Kernel. The Kernel is composed of values learned by the model. 
[see wiki](https://en.wikipedia.org/wiki/Kernel_(image_processing)).

Kernel layer libs : nvidia cuDNN / cuBLAS and intel MKL