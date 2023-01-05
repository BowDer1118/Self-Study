package com.bowder.maven;

import java.util.Scanner;

import net.sourceforge.pinyin4j.PinyinHelper;

//測試漢字轉拼音
public class PinyinTestor {
	public static void main(String[] args) {
		Scanner scanner = new Scanner(System.in);
		String string = scanner.nextLine();

		// 使用PinyinHelper將中文轉成漢字拼音(返回陣列的原因是因為可能會有破音字)
		String[] pinyinStrings = PinyinHelper.toHanyuPinyinStringArray(string.charAt(0));
		// 輸出漢字拚音
		for (String py : pinyinStrings) {
			System.out.println(py);
		}
	}
}
