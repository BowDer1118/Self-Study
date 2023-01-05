package com.bowder.factory;

import com.bowder.factory.i18n.I18N;
import com.bowder.factory.i18n.I18NFactory;

//程式的入口，系統要能根據不同地區顯示不同的語言
public class Software {
	public static void main(String[] args) {
		// 透過I18NFactory獲取I18N物件
		I18N i18n = I18NFactory.getI18NObject("china");
		System.out.println(i18n.getTitle());

	}
}
