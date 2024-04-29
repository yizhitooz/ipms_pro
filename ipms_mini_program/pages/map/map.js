// pages/charge/map.js
Page({

  /**
   * 页面的初始数据
   */
  data: {

  },

  /**
   * 生命周期函数--监听页面加载
   */
  onLoad(options) {
    wx.getLocation({
      type: 'wgs84', // 使用 GPS 坐标系
      success: (res) => {
        const latitude = res.latitude; // 纬度
        const longitude = res.longitude; // 经度
        console.log('当前位置：', latitude, longitude);
        // 更新页面数据
        this.setData({
          latitude: latitude,
          longitude: longitude
        });
      },
      fail: (res) => {
        console.log('获取位置失败：', res);
        // 处理获取位置失败的情况
      }
    })
  },

  /**
   * 生命周期函数--监听页面初次渲染完成
   */
  onReady() {

  },

  /**
   * 生命周期函数--监听页面显示
   */
  onShow() {

  },

  /**
   * 生命周期函数--监听页面隐藏
   */
  onHide() {

  },

  /**
   * 生命周期函数--监听页面卸载
   */
  onUnload() {

  },

  /**
   * 页面相关事件处理函数--监听用户下拉动作
   */
  onPullDownRefresh() {

  },

  /**
   * 页面上拉触底事件的处理函数
   */
  onReachBottom() {

  },

  /**
   * 用户点击右上角分享
   */
  onShareAppMessage() {

  },
  inputChange: function (e) {
    // 输入框内容变化时触发，可以在这里更新输入框的值
    console.log('输入框内容变化：', e.detail.value);
    this.setData({
      plateNumber: e.detail.value
    });
  },

  search: function () {
    // 点击查找按钮时触发，可以在这里处理查找逻辑
    console.log('点击了查找按钮');
    // 假设后端请求成功后返回车辆的坐标，并更新地图显示的位置
    const latitude = 25.317764 // 假设车辆纬度
    const longitude = 110.42232 // 假设车辆经度
    // 更新地图显示的位置
    this.setData({
      latitude: latitude,
      longitude: longitude,
      canNavigate: true // 开启导航按钮
    })
  },
  navigate: function () {
    wx.openLocation({
      latitude: 25.317764,
      longitude: 110.42232,
    })
  }
})