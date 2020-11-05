# 1.配置用户信息
```c++
git config --global user.name "ZainChen"  //设置用户名
git config --global user.email 2384439266@qq.com  //设置邮箱
git config --list  //查看配置信息
git config user.name  //查阅某个环境变量设定
```

# 2.Ubuntu创建git服务
```c++
sudo apt-get install git  //安装git
sudo adduser git  //创建一个git用户，用来运行git服
//创建证书登录：收集所有需要登录的用户的公钥，就是他们自己的id_rsa.pub文件，把所有公钥导入到/home/git/.ssh/authorized_keys文件里，一行一个。
sudo git init --bare sample.git  //初始化Git仓库：先选定一个目录作为Git仓库，假定是/zaingit/sample.git，在/zaingit目录下输入命令
sudo chown -R git:git sample.git  //把所有者改为git用户
//禁用shell登录:编辑/etc/passwd文件:类似"git:x:1000:1000:,,,:/home/git:/bin/bash"改为"git:x:1000:1000:,,,:/home/git:/usr/bin/git-shell"
git clone git@zainzy.com:/zaingit/sample.git  //克隆远程仓库,在各自的电脑上运行(显示下列内容成功:Cloning into 'sample'...\nwarning: You appear to have cloned an empty repository.)
```

## 2.1.创建git服务器仓库

```c++
sudo git init --bare zain.git  //初始化Git仓库：先选定一个目录作为Git仓库，假定是/zaingit/zain.git，在/zaingit目录下输入命令
sudo chown -R git:git zain.git  //把所有者改为git用户
git clone git@zainzy.com:/zaingit/zain.git  //克隆远程仓库
git remote add zain git@zainzy.com:/zaingit/zain.git  //将本地的仓库关联到服务器仓库，后面的https改成刚刚自己的地址(HTTPS和SSH都可以)(origin是本地默认的一个名称，可自定义)
git remote add zain git@zainzy.com:/zaingit/www.git
```

## 2.2.编写自动更新钩子
```c++
$ cd /zaingit/www.git/hooks/
$ vim /zaingit/www.git/hooks/post-receive
复制代码
'''
git --work-tree=/root/www checkout -f
'''
复制代码
给钩子文件添加执行权限
$ cd /zaingit/www.git/hooks/
$ chown git:git post-receive  //将该文件用户及用户组都设置成git
$ chmod +x post-receive  //给钩子文件添加执行权限
```


# 3.连接GitHub账号
```c++
ssh-keygen -t rsa -C "2384439266@qq.com"  //生成SSH Key
```

后面的 2384439266@qq.com 改为你在 github 上注册的邮箱，之后会要求确认路径和输入密码，我们这使用默认的一路回车就行。成功的话会在~/下生成.ssh文件夹，进去，打开 id_rsa.pub，复制里面的 key。
到 github 上，进入 Account => Settings（账户配置）。添加SSH keys。
验证是否成功：
```c++
ssh -T git@github.com
```
-
Hi ZainChen! You've successfully authenticated, but GitHub does not provide shell access.


# 4.Git 创建仓库(初始化 Git 仓库)
```c++
git init  //当前目录作为Git仓库
git init zain //指定目录作为Git仓库(在 zain 目录下会出现一个名为 .git 的目录)。
git add *.c  //告诉 Git 开始对这些文件进行跟踪(文件纳入版本控制，需要先用 git add 命令告诉 Git 开始对这些文件进行跟踪，然后提交)
git add README
git commit -m '初始化项目版本'
```

(以上命令将目录下以 .c 结尾及 README 文件提交到仓库中。)

# 5.克隆仓库

```c++
git clone <repo>  // 从现有 Git 仓库中拷贝项目到当前目录
git clone <repo> <directory> // 从现有 Git 仓库中拷贝项目到指定目录
```

(参数说明：repo:Git 仓库;directory:本地目录)
例：
比如，要克隆 Ruby 语言的 Git 代码仓库 Grit，可以用下面的命令：

```mysql
$ git clone git://github.com/schacon/grit.git
```

执行该命令后，会在当前目录下创建一个名为grit的目录，其中包含一个 .git 的目录，用于保存下载下来的所有版本记录。
如果要自己定义要新建的项目目录名称，可以在上面的命令末尾指定新的名字：

```mysql
$ git clone git://github.com/schacon/grit.git mygrit
```

## 5.1.各种写法
git clone 时，可以所用不同的协议，包括 ssh, git, https 等，其中最常用的是 ssh，因为速度较快，还可以配置公钥免输入密码。各种写法如下：

```mysql
git clone git@github.com:fsliurujie/test.git         --SSH协议
git clone git://github.com/fsliurujie/test.git          --GIT协议
git clone https://github.com/fsliurujie/test.git      --HTTPS协议
```


# 6.实践
## 6.1.初始化本地项目上传到GitHub指定项目中

```c++
git init  //当前目录作为Git仓库
echo "# zain" >> README.md  //创建README.md文件，写入相关内容
git add * //将项目中的所有文件添加到仓库中
git add README.md  //指定文件添加到仓库中
git status  //修改相应文件后查看当前的git仓库状态(查看仓库中哪些文件被改动)
git commit -m "first commit"  //提交到仓库
git remote add zain https://github.com/ZainChen/zain.git  //将本地的仓库关联到GitHub，后面的https改成刚刚自己的地址(HTTPS和SSH都可以)(origin是本地默认的一个名称，可自定义)
git pull zain master  //上传github之前pull一下，拉取当前分支最新代码(主分支)(远程库为空时次命令无效)
git push -u zain master  //上传代码到GitHub远程仓库(上传到主分支)
```

## 6.2.克隆GitHub指定项目到本地修改并提交

```c++
git clone git@github.com:ZainChen/LeidaMovie.git  //克隆GitHub指定项目到本地
cd LeidaMovie  //进入工程目录
git checkout gh-pages  //切换分支(gh-pages为目标切换分支)
git checkout master  //切换到主分支
git status  //修改相应文件后查看当前的git仓库状态(查看仓库中哪些文件被改动)
git add *  //将项目中的所有文件添加到仓库中
git commit -m "add all file"  //将暂存区里的改动给提交到本地版本库
git pull  //拉取当前分支最新代码
git push origin master  //push到远程master分支上
```

## 6.3.添加和删除文件

```c++
vim zain.txt  //创建文件zain.txt
git add zain.txt  //将zain.txt文件添加到仓库中
git commit -m 'add zain.txt'  //将暂存区里的改动给提交到本地版本库
git pull  //拉取当前分支最新代码
git push origin master  //push到远程master分支上
rm zain.txt  //删除本地文件zain.txt
git rm zain.txt  //删除版本库中zain.txt文件
git commit -m "remove zain.txt"  //将暂存区里的改动给提交到本地版本库
git pull  //拉取当前分支最新代码
git push origin master  //push到远程master分支上
```


## 6.4.分支操作
### 6.4.1.新建分支

```c++
git checkout -b zain  //新建zain分支
git branch -a  //查看当前所有的分支(结果显示带*号的，而且颜色是绿色的即为我们当前所在的分支)
git checkout zain  //切换到zain分支
git branch  //查看分支
git commit -m "master merge zain"  //合并分支提交
git pull origin zain  //拉取当前分支最新代码(origin是本地默认的一个名称，自己在新建本地仓库关联的时候是可以改名。平常使用的git pull都是默认从master分支上拉去代码。这里是从zain分支上拉取代码)
git push origin zain  //提交本地代码到zain分支
```

### 6.4.2.合并分支(方法1)

#### 6.4.2.1.zain 合并到 master

```c++
git checkout master  //切换到主分支master
git merge zain  //zain 合并到 master
git pull origin master
git push origin master
```

#### 6.4.2.2.master 合并到 zain

```c++
git checkout zain  //切换到分支zain
git merge master  //master 合并到 zain
git pull origin zain
git push origin zain
```

### 6.4.3.合并分支(方法2)
#### 6.4.3.1.zain 合并到 master

```c++
git checkout zain  //切换到分支zain
git rebase master    //zain 合并到  master
git checkout master  //切换到主分支master
git pull origin master
git push origin master
```

#### 6.4.3.2.master 合并到 zain

```c++
git checkout master  //切换到分支master
git rebase zain    //master 合并到 zain
git checkout zain  //切换到分支zain
git pull origin zain
git push origin zain
```

### 6.4.4.删除分支

```c++
git checkout master  //切换到分支master
git branch -d zain  //删除zain分支(删除本地分支)
git push origin :zain  //删除zain分支(删除远程分支)
```


# 7.查看修改前后具体变化
(注：以下命令可以不指定 (filename)，则对全部文件操作。 以下命令涉及和 Git仓库 对比的，均可指定 commit 的版本。)
## 7.1.工作目录 vs 暂存区
```c++
git diff (filename)  //工作目录 vs 暂存区
```

注：查看文件在工作目录与暂存区的差别。如果还没 add 进暂存区，则查看文件自身修改前后的差别。也可查看和另一分支的区别。

```c++
git diff (branch) (filename)  //工作目录 vs 暂存区(指定分支(branch))
```

## 7.2.暂存区 vs Git仓库
```c++
git diff --cached (filename)  //暂存区 vs Git仓库
```

注：表示查看已经 add 进暂存区但是尚未 commit 的内容同最新一次 commit 时的内容的差异。 也可以指定仓库版本：

```c++
git diff --cached (commit) (filename)  //暂存区 vs Git仓库(指定仓库(commit))
```

## 7.3.工作目录 vs Git仓库
```c++
git diff (commit) (filename)  //工作目录 vs Git仓库
```


注：查看工作目录同Git仓库指定 commit 的内容的差异。 (commit)=HEAD 时：查看工作目录同最近一次 commit 的内容的差异。

## 7.4.Git仓库 vs Git仓库
```c++
git diff (commit) (commit)  //Git仓库 vs Git仓库
//意义：Git仓库任意两次 commit 之间的差别。
//例：
git log  //查看git仓库版本id
git diff 4c543967f205baca240a1505cc8bec6b54324c3a 34025e8330903e813cfdf0382869bfbb6d18141b > ./diff.txt  //对比结果写入到文件diff.txt中
```

## 7.5.HEAD说明

```c++
HEAD //最近一次 commit
HEAD^  //上次提交
HEAD~100 //上100次提交
//每次提交产生的哈希值
```

# 8.查看两个分支差异

```c++
//假设有两个分支：master, zain
git log zain ^master  //查看 zain 有，而 master 中没有的
git log master ^zain  //查看 master 有，而 zain 中没有的
git log master..zain  //查看 zain 中比 master 中多提交了哪些内容(列出来的是两个点后边分支(此处即zain)多提交的内容)
git log zain..master  //查看 master 中比 zain 中多提交了哪些内容
git log zain...master  //查看 master 与 zain 的差异
git log --left-right dev...master  //查看 master 与 zain 的差异且显示每个提交是在哪个分支上(左箭头 < 表示是 dev 的，右箭头 > 表示是 master)
```

# 9.Git 查看提交历史

```c++
git log  //列出所有历史提交记录
git log --oneline  //查看历史记录的简洁的版本
git log --oneline --graph  //查看历史中什么时候出现了分支、合并
git log --reverse --oneline  //逆向显示所有日志
git log --author=zain --oneline -5  //查找指定用户的提交日志
//指定日期，可以执行几个选项：--since 和 --before，但是你也可以用 --until 和 --after。
//例:
git log --oneline --before={3.weeks.ago} --after={2010-04-18} --no-merges  //看 Git 项目中三周前且在四月十八日之后的所有提交(--no-merges 选项，隐藏合并提交)
```

# 10.创建和使用【.gitignore文件】

```c++
vim .gitignore  //创建.gitignore文件
```

.gitignore文件内容说明：

```bash
# #代表注释
/bin/*  #忽略根目录下bin文件夹中的所有文件
*.class  #忽略所有.class文件
!/bin/*.java  #不忽略根目录下bin文件夹中.java文件
```

# 11.重命名文件和文件夹

```c++
git mv -f oldfolder newfolder
git add -u newfolder  //-u 选项会更新已经追踪的文件和文件夹。
git commit -m "changed the foldername whaddup"

//在大小写不敏感的系统中，如windows，重命名文件的大小写,使用临时文件名
git mv foldername tempname && git mv tempname folderName
git mv -n foldername folderName  //(显示重命名会发生的改变，不进行重命名操作)
```





