package com.imooc.springbootlearn.controller;

import org.springframework.beans.factory.annotation.Value;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RestController;

/**
 * 和配置相關的Controller
 */
@RestController
public class PropertiesController {
    //透過@Value()從配置文檔中讀取數值
    @Value("${school.grade}")
    private Integer grade;
    @Value("${school.classNum}")
    private Integer classNum=9;
    //要注入static屬性需要將@Value寫在Setter上，並且Setter不能為static
    private static Integer age;

    @GetMapping("/grade_class")
    public String gradeClass(){
        return "年級: "+grade+" 班級: "+classNum;
    }

    @GetMapping("/static")
    public String staticPara(){
        return "靜態的年齡變數: "+age;
    }



    public Integer getGrade() {
        return grade;
    }

    public void setGrade(Integer grade) {
        this.grade = grade;
    }

    public Integer getClassNum() {
        return classNum;
    }

    public void setClassNum(Integer classNum) {
        this.classNum = classNum;
    }

    public Integer getAge() {
        return age;
    }

    @Value("${school.age}")
    public void setAge(Integer age) {
        PropertiesController.age = age;
    }
}
