package com.imooc.device;

import javax.servlet.http.HttpServletRequest;

public class DeviceFactory {
	public static Device getDevice(HttpServletRequest request) {
		// 獲得客戶端設備環境
		String userAgent = request.getHeader("user-agent");
		System.out.println(userAgent);
		// 判斷客戶端裝置
		if (userAgent.indexOf("Windows NT") != -1) {
			// 客戶端為PC
			return new DesktopDevice();
		} else if (userAgent.indexOf("iPhone") != -1 || userAgent.indexOf("Android") != -1) {
			// 客戶端為手機
			return new MoblieDevice();
		}
		return null;
	}
}
