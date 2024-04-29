// charge.js

Page({
  data: {
    parkingInfo: '' // 停车信息
  },
  onLoad: function(options) {
    // 获取传递过来的停车信息
    const parkingInfo = decodeURIComponent(options.info);
    this.setData({
      parkingInfo: parkingInfo
    });
  },
  onTapPay: function() {
    // 缴费操作，你可以在这里编写相应的逻辑
    wx.showToast({
      title: '缴费成功！',
      icon: 'success'
    });
  }
});
