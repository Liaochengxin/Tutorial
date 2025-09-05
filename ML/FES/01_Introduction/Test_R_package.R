# =======================================================
# R_package_install.R
# 自动安装 caret / tidymodels 及依赖，并检查失败包
# 适用于 macOS Homebrew R（使用 source 编译）
# =======================================================

# ---------------------------
# 1. 设置镜像源（清华 CRAN）
# ---------------------------
options(repos = c(CRAN = "https://mirrors.tuna.tsinghua.edu.cn/CRAN/"))

# ---------------------------
# 2. 需要安装的包列表（顶层包）
# ---------------------------
top_packages <- c("caret", "tidymodels")

# ---------------------------
# 3. 定义辅助函数：安装包并返回安装结果
# ---------------------------
install_package_safe <- function(pkg) {
  message("Installing package: ", pkg)
  result <- tryCatch({
    install.packages(pkg, dependencies = TRUE, type = "source")
    TRUE
  }, error = function(e) {
    message("❌ Failed to install ", pkg, ": ", e$message)
    FALSE
  })
  return(result)
}

# ---------------------------
# 4. 获取所有依赖包（递归）
# ---------------------------
get_all_dependencies <- function(pkgs) {
  deps <- tools::package_dependencies(pkgs, recursive = TRUE)
  unique(unlist(c(pkgs, deps)))
}

all_packages <- get_all_dependencies(top_packages)

# ---------------------------
# 5. 按顺序安装所有包
# ---------------------------
failed <- c()
for (pkg in all_packages) {
  # 如果已经安装，跳过
  if (pkg %in% rownames(installed.packages())) {
    message(pkg, " is already installed, skipping.")
    next
  }

  success <- install_package_safe(pkg)
  if (!success) failed <- c(failed, pkg)
}

# ---------------------------
# 6. 再次检查哪些包无法加载
# ---------------------------
not_loaded <- sapply(all_packages, function(p) {
  suppressWarnings(!require(p, character.only = TRUE))
})
failed_packages <- names(not_loaded[not_loaded])

# ---------------------------
# 7. 输出结果
# ---------------------------
if (length(failed_packages) == 0) {
  message("✅ All packages installed and loaded successfully!")
} else {
  message("⚠️ The following packages failed to install or load:")
  print(failed_packages)
  message("You can try installing them individually.")
}
