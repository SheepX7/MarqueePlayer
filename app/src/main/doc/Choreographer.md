## Choreographer
1. 关键 api：postCallback、postCallbackDelayed、postFrameCallback、postFrameCallbackDelayed

          public void postFrameCallback(FrameCallback callback) {
            postFrameCallbackDelayed(callback, 0);
          }

2. [Android 基于 Choreographer 的渲染机制详解](https://androidperformance.com/2019/10/22/Android-Choreographer/)  
   [Android 怎么就不卡了呢之Choreographer](https://juejin.cn/post/6844903818044375053)
   
3. 流程：
  - 获取线程单例 Choreographer 

     private static final ThreadLocal<Choreographer> sThreadInstance =
         new ThreadLocal<Choreographer>() {
           @Override
           protected Choreographer initialValue() {
               Looper looper = Looper.myLooper();
               if (looper == null) {
                   throw new IllegalStateException("The current thread must have a looper!");
               }
               Choreographer choreographer = new Choreographer(looper, VSYNC_SOURCE_APP);
               if (looper == Looper.getMainLooper()) {
                   mMainInstance = choreographer;
               }
               return choreographer;
            }
     };
    
  - postFrameCallback -> postCallbackDelayedInternal -> 
  - 