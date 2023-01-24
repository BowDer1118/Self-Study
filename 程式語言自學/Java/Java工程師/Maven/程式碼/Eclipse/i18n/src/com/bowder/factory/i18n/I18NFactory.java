package com.bowder.factory.i18n;

//面對使用者的工廠類，用以代替使用者選擇該創造的物件
public class I18NFactory {
	public static I18N getI18NObject(String area) {
		if (area.equals("china")) {
			return new Chinese();
		} else if (area.equals("spain")) {
			return new Spaninish();
		} else if (area.equals("Italy")) {
			return new Italian();
		} else {
			return null;
		}
	}
}
