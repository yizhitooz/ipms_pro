// index.js

Page({
  data: {
    parkingCapacity: 'XX/YY' // 初始实时容量数据
  },
  refreshCapacity: function () {
    this.setData({
      parkingCapacity: 'Updated XX/YY' // 更新实时容量数据
    })
  },
  scanQRCode: function (_options) {
    // 只允许从相机扫码
    wx.scanCode({
      onlyFromCamera: true,
      success(res) {
        console.log(res)
        const parkingInfo = res.result
        wx.navigateTo({
          url: '/pages/charge/charge?info=' + encodeURIComponent(parkingInfo)
        })
      }
    })
  },
  onTapOpenMap:function(_option){
    wx.navigateTo({
      url: '/pages/map/map'
    })
  },
  // 以下是添加的部分，用于触发扫码功能
  onTapScanQRCode: function () {
    // 点击按钮时触发扫码功能
    this.scanQRCode();
  },
  onTapPhoneCall:function(){
    wx.makePhoneCall({
      phoneNumber: '18172337091',
    })
  }
})