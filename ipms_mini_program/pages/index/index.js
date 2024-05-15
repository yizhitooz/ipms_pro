// index.js

Page({
    data: {
        current: 0,
        max: 300,
        parkingCapacity: '0/300'
    },
    onReady() {
        this.refreshCapacity()
    },
    refreshCapacity: function () {
        wx.request({
            url: 'http://localhost:8080/parking/lot/update/1',
            method: 'GET',
            success: (res) => {
                if (res.data.code == 200) {
                    const current = res.data.data.currentCarPark
                    const max = res.data.data.maxCarPark
                    this.setData({
                        current: current,
                        max: max,
                        parkingCapacity: `${current}/${max}`
                    })
                    console.log("parkingCapacity:" + this.data.parkingCapacity)
                } else {
                    wx.showToast({
                        title: '刷新失败',
                        icon: 'error'
                    })
                }
            },
            fail: (_res) => {
                wx.showToast({
                    title: '刷新失败',
                    icon: 'error'
                })
            }
        })
    },
    scanQRCode: function (_options) {
        // 只允许从相机扫码
        wx.scanCode({
            onlyFromCamera: true,
            success: (res) => {
                console.log(res)
                const parkingInfo = JSON.parse(res.result)

                wx.navigateTo({
                    url: '/pages/charge/charge?' +
                        'plate=' + encodeURIComponent(parkingInfo.plate) +
                        '&id=' + encodeURIComponent(parkingInfo.id)
                })
            },
            fail(_res) {
                wx.showToast({
                    title: '扫码失败',
                    icon: 'error'
                })
            }
        })
    },
    onTapOpenMap: function (_option) {
        wx.navigateTo({
            url: '/pages/map/map'
        })
    },
    onTapScanQRCode: function () {
        this.scanQRCode();
    },
    onTapPhoneCall: function () {
        wx.makePhoneCall({
            phoneNumber: '18172337091',
        })
    }
})