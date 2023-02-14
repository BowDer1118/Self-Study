package com.imooc.springbootlearn.service;

import com.imooc.springbootlearn.pojo.Student;
import org.junit.jupiter.api.Test;
import org.junit.runner.RunWith;
import org.springframework.boot.test.context.SpringBootTest;
import org.springframework.test.context.junit4.SpringRunner;

import javax.annotation.Resource;

import static org.junit.jupiter.api.Assertions.*;
//使用RunWith和SpringBootTest標籤來進行單元測試
@RunWith(SpringRunner.class)
@SpringBootTest
class StudentServiceTest {
    @Resource
    private StudentService studentService;
    @Test
    void getStudent() {
        Student student=studentService.getStudent(1);
        System.out.println(student);
    }
}