def get_segmentation_data_from_r():
    """
    从R的caret包直接获取segmentationData数据集
    需要先安装: pip install rpy2
    """
    try:
        import rpy2.robjects as robjects
        from rpy2.robjects import pandas2ri
        from rpy2.robjects.packages import importr
        from rpy2.robjects.conversion import localconverter

        # 导入R包
        utils = importr('utils')
        caret = importr('caret')

        # 加载数据
        robjects.r('data(segmentationData)')
        r_segmentationData = robjects.r('segmentationData')

        # 使用 localconverter 转换为 pandas DataFrame
        import pandas as pd
        with localconverter(robjects.default_converter + pandas2ri.converter):
            segmentationData = pandas2ri.rpy2py(r_segmentationData)

        print("✅ 成功从R获取 segmentationData 数据集")
        print(f"数据集形状: {segmentationData.shape}")

        #segmentationData.to_csv("./segmentationData.csv", index=False)
        #print("✅ CSV 已保存到当前目录: ./segmentationData.csv")

        return segmentationData

    except Exception as e:
        print(f"从R获取数据失败: {e}")
        return None


if __name__ == "__main__":
    data = get_segmentation_data_from_r()
    if data is not None:
        print(data.head())
