# 自动安装 caret 及依赖（macOS 优先二进制）
# --------------------------------------

# 1. 设置 CRAN 镜像（清华为主，CRAN 主站为备用）
options(repos = c(
  CRAN = "https://mirrors.tuna.tsinghua.edu.cn/CRAN/",
  CRAN2 = "https://cran.r-project.org/"
))

# 2. 优先使用二进制（binary），没有才回退到源码
options(pkgType = "both")

# 3. 要安装的包列表
packages <- c("caret", "tidymodels", "ggthemes", "pROC")

# 4. 检查哪些包未安装
installed <- packages %in% rownames(installed.packages())

# 5. 安装未安装的包
if(any(!installed)) {
  install.packages(packages[!installed], dependencies = TRUE, type = "source")
} else {
  message("所有包已安装，跳过安装")
}

# 6. 加载并验证包
for(pkg in packages) {
  library(pkg, character.only = TRUE)
  message(pkg, " version: ", as.character(packageVersion(pkg)))
}

message("✅ 所有 R 包安装并加载完成（优先二进制）")
