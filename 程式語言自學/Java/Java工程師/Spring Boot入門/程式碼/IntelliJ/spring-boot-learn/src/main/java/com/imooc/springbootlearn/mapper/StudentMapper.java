package com.imooc.springbootlearn.mapper;

import com.imooc.springbootlearn.pojo.Student;
import org.apache.ibatis.annotations.Mapper;
import org.apache.ibatis.annotations.Select;
import org.springframework.stereotype.Repository;

/**
 * 從資料庫獲取Student資料
 */
@Mapper
@Repository
public interface StudentMapper {
    @Select("SELECT * FROM student WHERE id = #{id}")
    public Student findById(Integer id);

}
