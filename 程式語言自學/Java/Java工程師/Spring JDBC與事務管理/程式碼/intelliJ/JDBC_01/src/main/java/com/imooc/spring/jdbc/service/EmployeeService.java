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
    //在需要事務管理的類中加入事務管理器
    private DataSourceTransactionManager transactionManager;



    //批量導入資料到資料庫中
    public void batchImport(){
        //定義事務默認的標準配置
        TransactionDefinition definition=new DefaultTransactionDefinition();
        //使用定義好的規則開始一個事務:代表從這行開始，往下都是一個事務
        //將事務記錄放在返回值TransactionStatus中
        TransactionStatus status=transactionManager.getTransaction(definition);

        //使用try-catch捕捉異常，如果捕捉到異常則rollback，沒有異常則commit
        try{
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
            //將到目前為止的事物提交:執行事務記錄中的操作
            transactionManager.commit(status);
            System.out.println("批量導入資料庫成功");
        }catch (Exception e){
            //發生異常
            transactionManager.rollback(status);
            System.out.println("發生異常"+e.getMessage());
        }
    }
    public EmployeeDao getEmployeeDao() {
        return employeeDao;
    }

    public void setEmployeeDao(EmployeeDao employeeDao) {
        this.employeeDao = employeeDao;
    }

    public DataSourceTransactionManager getTransactionManager() {
        return transactionManager;
    }

    public void setTransactionManager(DataSourceTransactionManager transactionManager) {
        this.transactionManager = transactionManager;
    }
}
