// pages/charge/map.js
Page({
    data: {
        user: {
            latitude: '',
            longitude: '',
        },
        car: {
            latitude: '',
            longitude: '',
        },
        // 观音山：25.301772,110.408534
        GYS: {
            latitude: '25.301772',
            longitude: '110.408534',
        },
        // 南大门：25.304346,110.419378
        NDM: {
            latitude: '25.304346',
            longitude: '110.419378',
        },
        markers: []
    },
    onLoad(_options) {
        wx.getLocation({
            type: 'wgs84', // 使用 GPS 坐标系
            success: (res) => {
                const latitude = res.latitude; // 纬度
                const longitude = res.longitude; // 经度
                console.log('当前位置：', latitude, longitude);
                // 更新页面数据
                this.setData({
                    user: {
                        latitude: latitude,
                        longitude: longitude
                    }
                })
            },
            fail: (_res) => {
                wx.showToast({
                    title: '定位失败',
                    icon: 'error'
                })
                this.setData({
                    // 花江校区：25.311923,110.416742
                    latitude: 25.311923,
                    longitude: 110.416742
                })
            }
        })
        const mapCtx = wx.createMapContext('map')
        mapCtx.moveToLocation()
    },
    inputChange: function (e) {
        console.log('输入框内容变化：', e.detail.value);
        this.setData({
            plate: e.detail.value
        });
    },

    search: function () {
        const plate = this.data.plate
        if (plate == null) {
            wx.showToast({
                title: '请输入车牌号',
                icon: 'error'
            })
        } else {
            wx.request({
                url: 'http://localhost:8080/carpark/plate/' + plate,
                method: 'GET',
                success: (res) => {
                    if (res.data.code == 200) {
                        const point = res.data.data.location
                        const regex = /POINT\((\d+\.\d+)\s(\d+\.\d+)\)/
                        const match = point.match(regex);
                        if (match) {
                            const longitude = parseFloat(match[1])
                            const latitude = parseFloat(match[2])
                            console.log('经度：', longitude)
                            console.log('纬度：', latitude)
                            this.setData({
                                car: {
                                    latitude: latitude,
                                    longitude: longitude
                                },
                                canNavigate: true, // 允许导航
                                markers: [{
                                    id: 0,
                                    latitude: latitude,
                                    longitude: longitude
                                }]
                            })
                        } else {
                            wx.showToast({
                                title: '没有找到匹配的坐标',
                                icon: 'error'
                            })
                        }
                    } else {
                        wx.showToast({
                            title: '查找失败',
                            icon: 'error'
                        })
                    }
                },
                fail: (_res) => {
                    wx.showToast({
                        title: '请求失败',
                        icon: 'error'
                    })
                    this.setData({
                        car: {
                            // 五教：25.314395,110.416903
                            latitude: 25.314395,
                            longitude: 110.416903
                        },
                        canNavigate: true
                    })
                }
            })
        }
    },
    navigateToCar: function () {
        wx.openLocation({
            latitude: parseFloat(this.data.car.latitude),
            longitude: parseFloat(this.data.car.longitude),
        })
    },
    navigateToGYS: function () {
        wx.openLocation({
            latitude: parseFloat(this.data.GYS.latitude),
            longitude: parseFloat(this.data.GYS.longitude),
        })
    },
    navigateToNDM: function () {
        wx.openLocation({
            latitude: parseFloat(this.data.NDM.latitude),
            longitude: parseFloat(this.data.NDM.longitude),
        })
    }
})