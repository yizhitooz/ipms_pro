// charge.js

Page({
    data: {
        parkingDetails: '停车信息：加载中...',
        currentDateTime: '',
        enterDateTime: '',
        plate: '',
        id: 0,
        fee: 0,
        btn_disable: false
    },
    currentDateTime: () => {
        const padZero = (num) => {
            return (num < 10 ? '0' : '') + num;
        };
        var currentDate = new Date();
        var year = currentDate.getFullYear()
        var month = padZero(currentDate.getMonth() + 1)
        var day = padZero(currentDate.getDate())
        var hours = padZero(currentDate.getHours())
        var minutes = padZero(currentDate.getMinutes())
        var seconds = padZero(currentDate.getSeconds())
        return String(`${year}-${month}-${day} ${hours}:${minutes}:${seconds}`)
    },
    calculateHourDifference: (dateString1, dateString2) => {
        const date1 = new Date(dateString1);
        const date2 = new Date(dateString2);
        // 检查日期是否有效
        if (isNaN(date1.getTime()) || isNaN(date2.getTime())) {
            console.log("Invalid date format");
            wx.navigateBack({
                delta: 1,
            })
            return NaN;
        }
        const differenceMs = Math.abs(date1 - date2)
        const differenceHours = differenceMs / (1000 * 60 * 60)

        return differenceHours
    },
    onLoad: function (options) {
        // 获取传递过来的停车信息
        var that = this
        console.log(options)
        if(options.plate==null||options.id==null){
            navigateBack({
                delta:1
            })
            wx.showToast({
              title: '二维码错误',
              icon:'error'
            })
        }
        const plate = decodeURIComponent(options.plate)
        const id = parseInt(options.id)
        this.setData({
            plate: plate,
            id: id
        });
        wx.request({
            url: 'http://localhost:8080/parking/record/search',
            data: {
                plate: this.data.plate,
                id: this.data.id,
            },
            method: "POST",
            header: {
                'content-type': 'application/json'
            },
            success: (res) => {
                if (res.data.code == 200) {
                    // 如果返回的状态码是 200
                    wx.showToast({
                        title: '扫码成功',
                        icon: 'success'
                    })

                    if (res.data.data.exitDateTime != null) {
                        wx.navigateBack({
                            delta: 1
                        })
                        wx.showToast({
                            title: '等待二维码刷新',
                            icon: 'loading'
                        })
                    }

                    const enterDateTime = res.data.data.enterDateTime
                    let hours = this.calculateHourDifference(this.currentDateTime(), enterDateTime)
                    let daysHours = {
                        days: Math.floor(hours / 24),
                        hours: (hours % 24).toFixed(2)
                    }
                    let fee = (daysHours.days * 60 + daysHours.hours * 8).toFixed(2)
                    const info = String(`车牌号：${this.data.plate}
                                        入场时间：${enterDateTime}
                                        当前时间：${this.currentDateTime()}
                                        停车时长：${daysHours.days}天   ${(daysHours.hours)}小时，
                                        缴费金额：${fee}元(RMB)
                                        (当前时间与缴费金额仅供参考，以实际缴费时间为准) `)
                    that.setData({
                        parkingDetails: info,
                        enterDateTime: enterDateTime,
                        currentDateTime: this.currentDateTime(),
                        id: res.data.data.id
                    })
                } else {
                    // 其他状态码
                    wx.navigateBack({
                        delta: 1
                    })
                    wx.showToast({
                        title: '二维码有误！',
                        icon: 'error'
                    })
                }
            },
            fail: function (_error) {
                wx.navigateBack({
                    delta: 1
                })
                wx.showToast({
                    title: '请求失败！',
                    icon: 'error'
                });
            }
        })
    },
    onTapPay: function () {
        wx.request({
            url: 'http://localhost:8080/vehicle/search',
            method: "POST",
            data: {
                plate: this.data.plate
            },
            success: (res) => {
                if (res.data.code == 200) {
                    const compareDates = (dateString1, dateString2) => {
                        const date1 = new Date(dateString1);
                        const date2 = new Date(dateString2);

                        if (date1 < date2) {
                            // date1 <- date2
                            return 0
                        } else if (date1 > date2) {
                            // date2 <- date1
                            return 1
                        } else {
                            return 0
                        }
                    }
                    let hours = this.calculateHourDifference(this.data.enterDateTime,
                        this.currentDateTime())
                    let daysHours = {
                        days: Math.floor(hours / 24),
                        hours: (hours % 24).toFixed(2)
                    }
                    let fee = (daysHours.days * 60 + daysHours.hours * 8).toFixed(2)

                    if (!compareDates(res.data.data.dueDate, this.currentDateTime())) {
                        wx.showModal({
                            title: '确认付款',
                            content: `你需要支付${fee}元(RMB)`,
                            complete: (res) => {
                                if (res.cancel) {
                                    wx.showToast({
                                        title: '取消支付！',
                                        icon: 'error'
                                    })
                                }
                                if (res.confirm) {
                                    wx.request({
                                        url: 'http://localhost:8080/parking/record/exit',
                                        method: "POST",
                                        data: {
                                            plate: this.data.plate,
                                            id: this.data.id
                                        },
                                        header: {
                                            'content-type': 'application/json'
                                        },
                                        success: (res) => {
                                            console.log(res)
                                            if (res.data.code == 200) {
                                                wx.navigateBack({
                                                    delta: 1
                                                })
                                                wx.showToast({
                                                    title: '缴费成功！',
                                                    icon: 'success'
                                                })
                                            } else {
                                                wx.showToast({
                                                    title: '缴费失败！',
                                                    icon: 'error'
                                                })
                                            }
                                        },
                                        fail: (_res) => {
                                            wx.showToast({
                                                title: '缴费失败！',
                                                icon: 'error'
                                            })
                                        }
                                    })
                                }
                            }
                        })
                    } else {
                        wx.request({
                            url: 'http://localhost:8080/parking/record/exit',
                            method: "POST",
                            data: {
                                plate: this.data.plate,
                                id: this.data.id,
                            },
                            method: "POST",
                            header: {
                                'content-type': 'application/json'
                            },
                            success: (_res) => {
                                wx.showModal({
                                    title: '车位租赁',
                                    content: `本次停车无需停车费。
                                            提醒您，车位租赁到期时间：${res.data.data.dueDate}
                                            点击确认退出界面`,
                                    complete: (res) => {
                                        if (res.cancel) {
                                            btn_disable = true
                                        }
                                        if (res.confirm) {
                                            wx.navigateBack({
                                                delta: 1,
                                            })
                                        }
                                    }
                                })
                            },
                            fail: (_res) => {
                                wx.showToast({
                                    title: '请求失败',
                                    icon: 'error'
                                })
                            }
                        })
                    }
                } else {
                    wx.showToast({
                        title: '请求方法有误',
                        icon: 'error'
                    })
                }
            },
            fail: (_res) => {
                wx.showToast({
                    title: '请求失败',
                    icon: 'error'
                })
            }
        })
    }
})