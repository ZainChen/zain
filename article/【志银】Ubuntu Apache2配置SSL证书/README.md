# 【志银】Ubuntu Apache2配置SSL证书

---

# 1.准备工作

　　证书文件：`zain.crt`、`zain.key`

　　`/etc/apache2/`文件夹下新建ssl 文件夹，将证书文件放入`/etc/apache2/ssl`

# 2.配置SSL证书

　　打开` /etc/apache2/sites-available/default-ssl.conf`

```assembly
vim /etc/apache2/sites-available/default-ssl.conf
```

　　`ServerAdmin`下另起一行加上`"ServerName 你的域名:443"`

　　找到`SSLEngine`,`SSLCertificateFile`,`SSLCertificateKeyFile`，修改成以下内容：

```assembly
SSLEngine on
SSLCertificateFile /etc/apache2/ssl/zain.crt
SSLCertificateKeyFile /etc/apache2/ssl/zain.key
```

　　SSL证书配置完毕，保存退出(:wq)。

# 3.配置HTTPS 强制跳转

　　打开`/etc/apache2/sites-available/000-default.conf`

```assembly
vim /etc/apache2/sites-available/000-default.conf
```

　　`<VirtualHost *:80></VirtualHost>`标签内随便一个地方加入以下三行

```assembly
RewriteEngine on
RewriteCond  %{HTTPS} !=on
RewriteRule  ^(.*) https://%{SERVER_NAME}$1 [L,R]
```

　　打开`/etc/apache2/apache2.conf`

```assembly
vim /etc/apache2/apache2.conf
AllowOverride None
改为->
AllowOverride ALL
```

# 4.启动生效

　　启动 rewrite mod

```
sudo a2enmod rewrite
```

　　重启Apache2

```
sudo /etc/init.d/apache2 restart
```

> 志银(ZainChen)