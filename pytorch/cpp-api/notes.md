Building pytorch from sources:

```
-DUSE_CUDA=OFF \
-DUSE_OPENCL=ON \
-DUSE_NCCL=OFF \
-DUSE_NUMA=OFF \
-DUSE_GLOO=OFF \
-DUSE_MPI=OFF \
-DBUILD_TORCH=ON \
-DCMAKE_INSTALL_PREFIX=$PYTORCH_RELEASE_PATH
```

**Remark** I came across a compile error in caffe2:

```
/pytorch/caffe2/contrib/opencl/context.cc:10:24: error: expected '>'
CAFFE_KNOWN_TYPE(Tensor<OpenCLContext>);
```

Just to give it a try, commenting out this line make the build succeed
(but i don't know if there are some side effects).
