package com.imooc.springbootlearn.service;

import com.imooc.springbootlearn.mapper.StudentMapper;
import com.imooc.springbootlearn.pojo.Student;
import org.springframework.stereotype.Service;

import javax.annotation.Resource;

@Service
public class StudentService {
    @Resource
    private StudentMapper studentMapper;

    public Student getStudent(Integer id){
        Student student=studentMapper.findById(id);
        return student;
    }
}
