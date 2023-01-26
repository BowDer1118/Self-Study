import com.imooc.spring.jdbc.dao.EmployeeDao;
import com.imooc.spring.jdbc.entity.Employee;
import com.imooc.spring.jdbc.service.EmployeeService;
import org.junit.Test;
import org.junit.runner.RunWith;
import org.springframework.test.context.ContextConfiguration;
import org.springframework.test.context.junit4.SpringJUnit4ClassRunner;

import javax.annotation.Resource;
import java.util.Date;
import java.util.List;
import java.util.Map;

@RunWith(SpringJUnit4ClassRunner.class)
@ContextConfiguration(locations = {"classpath:applicationContext.xml"})
public class JdbcTemplateTester {
    //注入employeeDao物件
    @Resource
    private EmployeeDao employeeDao;

    @Resource
    private EmployeeService employeeService;
    @Test
    public void testFindById(){
        Employee employee=employeeDao.findById(3308);
        System.out.println(employee);
    }

    @Test
    public void testFindByDname(){
        List<Employee> employeeList=employeeDao.findByDname("研發部");
        for(Employee e:employeeList){
            System.out.println(e);
        }
    }

    @Test
    public void testFindMapByDname(){
        List<Map<String, Object>> mapList = employeeDao.findMapByDname("研發部");
        for(Map<String,Object> map:mapList){
            System.out.println(map);
        }
    }
    @Test
    public void testInsert(){
        Employee employee=new Employee();
        employee.setEno(8888);
        employee.setEname("德寶");
        employee.setSalary(8888f);
        employee.setDname("研發部");
        employee.setHiredate(new Date());
        employeeDao.insert(employee);
    }

    @Test
    public void testUpdate(){
        Employee employee=employeeDao.findById(8888);
        employee.setSalary(employee.getSalary()+1000f);
        int count=employeeDao.update(employee);
        System.out.println("已更新"+count+"筆資料");

    }

    @Test
    public void testDelete(){
        int count=employeeDao.delete(8888);
        System.out.println("已刪除"+count+"筆資料");
    }

    @Test
    public void testBatchImport(){
        employeeService.batchImport();
    }
}
