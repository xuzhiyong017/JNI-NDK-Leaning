# JNI-NDK-Leaning

SDL学习, 主函数入口，当然可以更灵活的通过jni去调用
```
子线程普通情况下是不能更新UI的，只要是 ViewRootImpl 
创建的线程就可以 touch view，然后 WindowManger.addView 
的时候又会去创建 ViewRootImpl，所以我们只要在子线程调用 
WindowManger.addView，这个时候添加的这个 View，
就只能在这个子线程刷新了，这个子线程就是这个 View 的 UI 线程了,
有些情况例外,比如说TextView这种控件，在内容没有达到引起布局变化的情况下，
子线程是可以更新text内容的，当需要更新布局的时候就会一起UI线程检测
```
