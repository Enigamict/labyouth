排他制御

排他制御とは、ダブルブッキング(同時に使う事)を防ぐために行う処理。

マルチスレッドプログラミングでスレッド間で共有データにアクセスするときに、mutex(MUTual EXclusion, ミューテックス)を用いて、排他ロックを行う。

排他ロックはデータベースシステムなどで記憶領域への同時アクセスを制限するロック機構

排他制御をしないと失われるもの(計算の整合性、データの整合性 etc…)

スレッドはちなみにプロセス内で独立で動作する関数と考えれば良い

クリティカルリージョンとは

ある部分の実行を開始したプロセスが、他のプロセスが同じ部分を実行する前にその処理を
終了する必要があるコード領域

例としてグローバル変数Vから減算して、減算した値をグローバル変数Wに増算する。

つまり同時に実行されるとおかしくなる処理

考え方としては、マルチスレッド機構を作る上で共有された資源を安全に使用する事が出来る事を保証する


mutex は二つの状態を取りうる。それは、アンロック状態(どのスレッドにも 保有されていない)とロック状態(一つのスレッドに保有されている)である。 二つの異なるスレッドが同時に一つの mutex を保有することはない。既に他の スレッドによってロックされた mutex をロックしようとするスレッドは、保有 側のスレッドが先にその mutex をアンロックするまで実行を停止させられる。([https://linuxjm.osdn.jp/html/glibc-linuxthreads/man3/pthread_mutex_lock.3.html](https://linuxjm.osdn.jp/html/glibc-linuxthreads/man3/pthread_mutex_lock.3.html))

セマフォとは
排他制御のための仕組みで、mutxとはまた別のもの

プロセスとは
非同期処理、子プロセス、親プロセスと決めて処理する。

## mutex

**mutex** は、初期化と破棄が必要

**mutex** の初期化

```
pthread_mutex_t fastmutex = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_init(&mutex, NULL);

```

```
int
pthread_mutex_init(pthread_mutex_t *mutex,
     const pthread_mutexattr_t *attr);

```

pthread_mutex_destroy()はpthread_mutex_tを引数に取り、mutxオブジェクトを破棄する。

```
pthread_mutex_destroy(&mutex);
```

[PTHREAD_MUTEX](https://linuxjm.osdn.jp/html/glibc-linuxthreads/man3/pthread_mutex_lock.3.html)

スレッドの作成

**int pthread_create(pthread_t *** *thread***, pthread_attr_t *** *attr***, void * (****start_routine***)(void *), void *** *arg***);**

**pthread_create**は呼び出しスレッドと並行して実行する、新しい制御スレッドを生成する。

int **pthread_mutex_lock(pthread_mutex_t ****mutex***));**

 pthread_mutex_lock()はオブジェクトをロックする。

([https://linuxjm.osdn.jp/html/glibc-linuxthreads/man3/pthread_mutex_lock.3.html](https://linuxjm.osdn.jp/html/glibc-linuxthreads/man3/pthread_mutex_lock.3.html))

pthread_mutex_unlock()はmutxオブジェクトをアンロックする。

([https://nxmnpg.lemoda.net/ja/3/pthread_mutex_unlock](https://nxmnpg.lemoda.net/ja/3/pthread_mutex_unlock))

対象の処理を囲む事によりロック状態とアンロック状態にする。

```
pthread_mutex_lock(&pdata->mutex);
pdata->data++;
pthread_mutex_unlock(&pdata->mutex);
```

各スレッドでmutxオブジェクトを使い回すようなイメージ

int pthread_join(pthread_t thread, void **retval);

pthread_join()はスレッドの終了を待つ

pthread_tはスレッドの識別子

表示させる
```
newThread(&thread1, (void *)loop1, &pth);
printf("%p\n", thread1);
newThread(&thread2, (void *)loop2, &pth);
printf("%p\n", thread2);
newThread(&thread3, (void *)loop3, &pth);
printf("%p\n", thread3);
```