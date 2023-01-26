package com.imooc.spring.jdbc.dao;

import com.imooc.spring.jdbc.entity.Employee;
import org.springframework.jdbc.core.BeanPropertyRowMapper;
import org.springframework.jdbc.core.JdbcTemplate;

import java.util.List;
import java.util.Map;

/**
 * 對資料庫中employee資料表訪問的Data Access Object
 */
public class EmployeeDao {
    private JdbcTemplate jdbcTemplate; //持有資料庫訪問物件
    //依照id查詢
    public Employee findById(Integer eno){
        //查詢語法
        String sql="select * from employee where eno = ?";
        //查詢參數
        Object[] queryParameters={eno};
        //依照bean的屬性和資料庫中的屬性一一對應
        BeanPropertyRowMapper<Employee> beanPropertyRowMapper=
                new BeanPropertyRowMapper<Employee>(Employee.class);
        /**
         *  queryForObject進行指定查詢後，將找到的唯一資料轉換為物件
         *  sql 為查詢語法
         *  queryParameters 為要填充的字串
         *  BeanPropertyRowMapper<Employee>(Employee.class) 要與資料表屬性對應的類別
         *
         *  @return Employee 代表查詢到的唯一返回資料(已經包裝成Employee類了)
         */
        Employee employee=jdbcTemplate.
                queryForObject(sql,queryParameters,beanPropertyRowMapper);
        return employee;
    }

    public List<Employee> findByDname(String dname){
        String sql="select * from employee where dname=?";
        Object[] parameters={dname};
        BeanPropertyRowMapper<Employee> beanPropertyRowMapper=
                new BeanPropertyRowMapper<>(Employee.class);
        //query會返回List集合
        List<Employee> employeeList=
                jdbcTemplate.query(sql,parameters,beanPropertyRowMapper);
        return employeeList;
    }

    public List<Map<String, Object>> findMapByDname(String dname){
        String sql="select eno as empno , salary as s from employee where dname=?";
        Object[] parameters={dname};
        /**
         * queryForList會將查詢到的資料表欄位與數值以List<Map<String,Object>>方式回傳
         * Map<String,Object> 每筆資料由資料表欄位和數值的key-value pair組合成Map
         * List 用來乘載多組Map物件也就是多筆的返回資料
         */
        List<Map<String, Object>> mapList = jdbcTemplate.queryForList(sql, dname);
        return mapList;
    }

    public void insert(Employee employee){
        //插入資料語法
        String sql="insert into employee (eno,ename,salary,dname,hiredate) " +
                "values (?,?,?,?,?)";
        Object[] parameters={employee.getEno(),employee.getEname(),employee.getSalary(),employee.getDname(),employee.getHiredate()};
         //update可以用來Create,update,delete
        jdbcTemplate.update(sql,parameters);
        System.out.println("以插入:"+employee);
    }

    public int update(Employee employee){
        //更新語法
        String sql="UPDATE employee SET ename=?, salary=?, dname=?, hiredate=? " +
                "WHERE eno=?";
        Object[] parameters={employee.getEname(),employee.getSalary(),employee.getDname(),employee.getHiredate(),employee.getEno()};
        //update會依照sql的問號順序依次將parameters的元素填充進去，並返回修改的資料數量
        int count=jdbcTemplate.update(sql,parameters);
        return count;
    }

    public int delete(Integer eno){
        String sql="delete from employee where eno=?";
        Object[] parameter={eno};
        int count= jdbcTemplate.update(sql,eno);
        return count;
    }

    public JdbcTemplate getJdbcTemplate() {
        return jdbcTemplate;
    }

    public void setJdbcTemplate(JdbcTemplate jdbcTemplate) {
        this.jdbcTemplate = jdbcTemplate;
    }


}
