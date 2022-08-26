# 使用说明

将以下代码编写为 `.bat` 脚本双击即可运行

```bat
start python local.py
start python listen.py -p 8000 -u u1:p1,u2:p2
start python slave.py -r 127.0.0.1:8000 -u u1:p1 -p 8001 -l 127.0.0.1:8002
start python remote.py
```

2018.06.14