This project shows how to use QPalette to adjus a window's colors. 
```
    contentFrame->setAutoFillBackground(true);
    QPalette p = contentFrame->palette(); //获取contentFrame的调色板信息
    p.setColor(QPalette::Window, color); //第一个参数为颜色主题，window类颜色即背景色
    contentFrame->setPalette(p);
    contentFrame->update();
```

ContentFrame here is a child window which is used to show how QPalette works. 
`QPaltte::Window` means background.  
