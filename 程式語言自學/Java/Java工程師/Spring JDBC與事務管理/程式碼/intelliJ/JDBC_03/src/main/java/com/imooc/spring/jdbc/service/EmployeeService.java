package com.imooc.spring.jdbc.service;

import com.imooc.spring.jdbc.dao.EmployeeDao;
import com.imooc.spring.jdbc.entity.Employee;
import org.springframework.stereotype.Service;
import org.springframework.transaction.annotation.Propagation;
import org.springframework.transaction.annotation.Transactional;

import javax.annotation.Resource;
import java.util.Date;

@Service
//聲明式事務核心註解
//放在類上代表將聲明式事務配置應用在當前類的所有方法，默認事務傳播方式為:REQUIRED
@Transactional(propagation = Propagation.REQUIRED)
public class EmployeeService {
    @Resource
    private EmployeeDao employeeDao;
    @Resource()
    private BatchService batchService;

    @Transactional(propagation = Propagation.NOT_SUPPORTED,readOnly = true)
    public Employee findById(Integer eno){
        return employeeDao.findById(eno);
    }

    public void batchImport() {
        for (int i = 1; i <= 10; i++) {
            /*if(i==3){
                throw new RuntimeException("意料之外的异常");
            }*/
            Employee employee = new Employee();
            employee.setEno(8000 + i);
            employee.setEname("员工" + i);
            employee.setSalary(4000f);
            employee.setDname("市场部");
            employee.setHiredate(new Date());
            employeeDao.insert(employee);
        }
    }

    public void startImportJob(){
        batchService.importJob1();
        if(1==1){
            throw new RuntimeException("意料之外的异常");
        }
        batchService.importJob2();
        System.out.println("批量导入成功");
    }

    public EmployeeDao getEmployeeDao() {
        return employeeDao;
    }

    public void setEmployeeDao(EmployeeDao employeeDao) {
        this.employeeDao = employeeDao;
    }

    public BatchService getBatchService() {
        return batchService;
    }

    public void setBatchService(BatchService batchService) {
        this.batchService = batchService;
    }
}
