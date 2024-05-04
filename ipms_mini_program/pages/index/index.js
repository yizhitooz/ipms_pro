// index.js

Page({
    data: {
        parkingCapacity: '142/250' // 初始实时容量数据
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
                const parkingInfo = JSON.parse(res.result)

                wx.navigateTo({
                    url: '/pages/charge/charge?' +
                        'plate=' + encodeURIComponent(parkingInfo.plate) +
                        '&id=' + encodeURIComponent(parkingInfo.id)
                })
            },fail(_res){
                wx.showToast({
                  title: '扫码失败',
                  icon:'error'
                })
            }
        })
    },
    onTapOpenMap: function (_option) {
        wx.navigateTo({
            url: '/pages/map/map'
        })
    },
    // 以下是添加的部分，用于触发扫码功能
    onTapScanQRCode: function () {
        // 点击按钮时触发扫码功能
        this.scanQRCode();
    },
    onTapPhoneCall: function () {
        wx.makePhoneCall({
            phoneNumber: '18172337091',
        })
    }
})