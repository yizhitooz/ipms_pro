// pages/charge/map.js
Page({

    /**
     * 页面的初始数据
     */
    data: {
        plate: ''
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
                                latitude: latitude,
                                longitude: longitude,
                                canNavigate: true // 开启导航按钮
                            })
                        } else {
                            console.log('没有找到匹配的坐标')
                        }
                    } else {
                        wx.showToast({
                            title: '查找失败',
                            icon: 'error'
                        })
                    }
                }
            })
        }
    },
    navigate: function () {
        wx.openLocation({
            latitude: this.data.latitude,
            longitude: this.data.longitude,
        })
    }
})