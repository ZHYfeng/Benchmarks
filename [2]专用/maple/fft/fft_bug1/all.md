#/home/zhy/Benchmarks/fft/fft_bug1
1.BUG1:Multi threads read and write global id without locks
- 函数SlaveStart()中line=431，修改为:
```c
  // LOCK(Global->idlock);
    MyNum = Global->id;
    assert(MyNum == Global->id);
    Global->id++;
  // UNLOCK(Global->idlock); 
```
- 已测试



