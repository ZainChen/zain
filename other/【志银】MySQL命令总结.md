# 0.MySQL密码设置
## 0.1.登入和进入MySQL数据库
### 0.1.1.登入MySQL数据库

//初始mysql默认没有密码,可以直接回车进入,有密码的需要输入密码

```mysql
C:\Users\Administrator>mysql -u用户名 -hMySQL服务器地址 -p
		Enter password:用户密码
					例:mysql -uroot -hlocalhost -p
		Enter password:******** //我的密码时是11111111
```
### 0.1.2.进入MySQL数据库

```mysql
mysql>use mysql;
```

## 0.2-给root用户设置密码
```mysql
mysql>update user set password=password("新密码") where user="root";
　　例:update user set password=password("11111111") where user="root";
```

## 0.3.刷新数据库(一定要记得)

```mysql
mysql>flush privileges;
```

## 0.4.退出mysql

```mysql
mysql>quit
```

# 1.MySQL服务器相关命令
## 1.1.连接MySQL服务器
```mysql
　 \>mysql -uroot -h127.0.0.1 -ppassword
　 \>mysql -u用户名 -hMySQL服务器地址 -p用户密码
例:\>mysql -uroot -hlocalhost -p11111111
```
## 1.2.断开MySQL服务器

```mysql
mysql>quit;
```

## 1.3.停止MySQL服务器

```
   1)\>net stop mysql
 或2)\>mysqladmin -uroot shutdown -ppassword
　例:\>mysqladmin -uroot shutdown -p11111111
```

## 1.4.启动MySQL服务器

```mysql
net start mysql
```

# 2.MySQL数据库操作
## 2.1.创建数据库

```mysql
　 create database 数据库名;
例:create database db_czy;
```

## 2.2.查看数据库

```mysql
show databases;
```

## 2.3.选择数据库

```mysql
use db_czy;
```

## 2.4.删除数据库

```mysql
　 drop database 数据库名;
例:drop database db_czy;
```


# 3.MySQL数据表操作
## 3.1.在当前选择的数据库中创建数据表
```mysql
create table 数据表名(字段名1 属性,字段名2 属性,...);
例:
create table tb_people(
  id int auto_increment primary key,
  user varchar(30) not null,
  password varchar(30) not null,
  email varchar(50) not null,
  createtime datetime
);
```
## 3.2.查看当前选择的数据库中的数据表

```mysql
show tables;
```

## 3.3.查看表结构

### 3.3.1.方法1

```mysql
　 show columns from 数据表名 from 数据库名;
例:show columns from tb_people from db_czy;
```

### 3.3.2.方法2

```mysql
　 show columns from 数据库名.数据表名;
例:show columns from db_czy.tb_people;
```

### 3.3.3.方法3

```mysql
　 describe 数据表名;
例:describe tb_people;
```

### 3.3.4.方法4

//可以只列出某一列信息

```mysql
　 desc 数据表名 列名;
例:describe tb_people password;
```

## 3.4.修改表结构

//添加一个新字段email,类型为varchar(50),not null,将字段user的类型改为varchar(40).

```mysql
　 alter table 数据表名 相关操作;
例:alter table tb_people add email varchar(50) not null, modify user varchar(40);
```

## 3.5.重命名表

```mysql
　 rename table 数据表名1 to 数据表名2;
例:rename table tb_people to tb_czy;
例:rename table tb_czy to tb_people;
```

## 3.6.删除表

```mysql
　 drop table 数据表名;
例:drop table tb_people;
```

# 4.MySQL数据增删查改操作
## 4.1.插入记录

//一次可插入多行记录,标准SQL语句只能一次插一行

`insert into 数据表名(字段名1,字段名2,..)values(值1,值2,..);`

```mysql
insert into tb_people(user,password,email,createtime) values('czy','11111111','2384439266@qq.com','2016-10-10 02:36:50');
insert into tb_people(user,password,email,createtime) values('cml','22222222','22222222@qq.com','2016-10-10 02:40:36');
//values('wha','33333333','33333333@qq.com','2016-10-10 02:45:25');
```
## 4.2.删除记录

//一般条件是指定id删除的,没有where条件则删除整个表

```mysql
　 delete from 数据表名 where 条件
例:delete from tb_people where user='wha';
```

## 4.3.查询数据库记录
### 4.3.1.方法1

//查询指定表内所有数据

```mysql
　 select * from 数据表;
例:select * from tb_people;
```

### 4.3.2.方法2

//查询指定数据库的指定表内的数据

```mysql
　 select * from 数据库名.数据表名;
例:select * from db_czy.tb_people;
```

### 4.3.3.方法3

//查询指定表内指定字段和某字段值数据

```mysql
　 select 部分字段名 from 数据表 where 查询的相关条件;
例:select id,user,password,email from tb_people where id=1;
```

## 4.4.修改记录

`update 数据表名 set column_name1=new_value1,..[where condition];`
`update 数据表名 set 字段名1=新的值1,字段名2=新的值2,.. [where 条件];`

```mysql
update tb_people set password='12345678',email='15707950645@163.com' where user='czy';
```
# 5.MySQL数据备份和恢复
## 5.1.数据备份
```mysql
　 mysqldump -u用户名 -p用户密码 数据库名 >备份文件储存路径和文件名
例:mysqldump -uroot -p11111111 db_czy >D:\File\phpEnv\MySQL\data_backup.txt
```

## 5.2.数据恢复
```mysql
　 mysql -u用户名 -p用户密码 数据库名 <要恢复的文件储存路径和文件名
例:mysql -uroot -p11111111 db_czy <D:\File\phpEnv\MySQL\data_backup.txt
```

> 志银(ZainChen)