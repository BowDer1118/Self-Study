package com.imooc.spring.jdbc.service;

import com.imooc.spring.jdbc.dao.EmployeeDao;
import com.imooc.spring.jdbc.entity.Employee;
import org.springframework.jdbc.datasource.DataSourceTransactionManager;
import org.springframework.transaction.TransactionDefinition;
import org.springframework.transaction.TransactionStatus;
import org.springframework.transaction.support.DefaultTransactionDefinition;

import java.util.Date;

//提供Employee類的相關工作
public class EmployeeService {
    private EmployeeDao employeeDao;
    //批量導入資料到資料庫中
    public void batchImport(){
            for(int i=0;i<10;i++){
//                if(i==3){
//                    throw new RuntimeException("意料之外的異常");
//                }
                Employee employee=new Employee();
                employee.setEno(8000+i);
                employee.setEname("員工"+i);
                employee.setSalary(4000f);
                employee.setDname("市場部");
                employee.setHiredate(new Date());
                employeeDao.insert(employee);
            }
            System.out.println("批量導入資料庫成功");
    }
    public EmployeeDao getEmployeeDao() {
        return employeeDao;
    }

    public void setEmployeeDao(EmployeeDao employeeDao) {
        this.employeeDao = employeeDao;
    }

}
