//index.js
//获取应用实例
const app = getApp()

Page({
  jj:function(){
  wx.navigateTo({
    url: '../in/in',
  })
  },
  ss:function(){
    wx.navigateTo({
      url: '../out/out',
    })
    },
  
 

  data: {
    integral: 0,          // 积分默认
    moneyNum: null,           // 用户输入的积分

    motto: 'Hello World',
    userInfo: {},
    hasUserInfo: false,
    canIUse: wx.canIUse('button.open-type.getUserInfo')
   
  },
  
  

//用wx.request进行与onenet的交流
  OneNet_Post:function(){
    var that=this
    let deviceid = "**********"
    let apikey = "**********************"
    let data={
        "datastreams": [{
                "id": "abc",
                "datapoints": [{
                      
                        "value": "1"
                    }
                   
                ]
            },
            
        ]
  
     }
    wx.request({
      url: "https://api.heclouds.com/devices/" + deviceid + "/datapoints",
      method:'POST',
      header:{
        "content-type": 'application/json',
        "api-key": apikey
      },
      data:JSON.stringify(data),
      success(res){
        console.log("更新数据成功",res)
      },
      fail: function(res){
        wx.showToast({ title: '系统错误' })
      },
      complete:function(res){
        wx.hideLoading()
      }
    })

  },
  
  

  onShareAppMessage: function() {
    var student = wx.getStorageSync('student')
		wx.showShareMenu({
	      withShareTicket: true,
	      menus: ['shareAppMessage', 'shareTimeline']
	    })
	},
	//用户点击右上角分享朋友圈
	onShareTimeline: function () {
		return {
	      title: '',
	      query: {
	        key: value
	      },
	      imageUrl: ''
	    }
	},
  //用wx.navigateTo进行跳转
  bindViewTap: function() {
    wx.navigateTo({
      url: '../logs/logs'
    })
  },
//用wx.showmodal设置弹窗
  getIntegral: function(e) {
      wx.showModal({
  
        title: '警告',
   
        content: '房门为开启状态',
        confirmText:'查看',
        confirmColor:'#DC143C',
        cancelText:'忽略',
   
        success: function (res) {
   
          if (res.confirm) {//这里是点击了确定以后
   
            console.log('用户点击确')
            wx.reLaunch({
              url: '../in/in',
                })
   
          } else {//这里是点击了取消以后
   
            console.log('用户点击取消')
   
          }
   
        }
   
      })
  },

  onLoad: function () {
    
    
    if (app.globalData.userInfo) {
      this.setData({
        userInfo: app.globalData.userInfo,
        hasUserInfo: true
      })
    } else if (this.data.canIUse){
      // 由于 getUserInfo 是网络请求，可能会在 Page.onLoad 之后才返回
      // 所以此处加入 callback 以防止这种情况
      app.userInfoReadyCallback = res => {
        this.setData({
          userInfo: res.userInfo,
          hasUserInfo: true
        })
      }
    } else {
      // 在没有 open-type=getUserInfo 版本的兼容处理
      wx.getUserInfo({
        success: res => {
          app.globalData.userInfo = res.userInfo
          this.setData({
            userInfo: res.userInfo,
            hasUserInfo: true
          })
        }
      })
    }
  },
  getUserInfo: function(e) {
    console.log(e)
    app.globalData.userInfo = e.detail.userInfo
    this.setData({
      userInfo: e.detail.userInfo,
      hasUserInfo: true
    })
  }
})
