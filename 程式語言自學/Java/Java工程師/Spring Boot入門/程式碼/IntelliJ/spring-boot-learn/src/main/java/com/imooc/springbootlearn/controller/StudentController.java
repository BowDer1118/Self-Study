package com.imooc.springbootlearn.controller;

import com.imooc.springbootlearn.service.StudentService;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RequestParam;
import org.springframework.web.bind.annotation.RestController;

import javax.annotation.Resource;

@RestController
public class StudentController {
    @Resource
    private StudentService studentService;

    @GetMapping("/student")
    public String requestPara(@RequestParam Integer id){
        return studentService.getStudent(id).toString();
    }
}
