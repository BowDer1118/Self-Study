package com.imooc.restful.controller;

import com.imooc.restful.entity.Person;
import org.springframework.stereotype.Controller;
import org.springframework.web.bind.annotation.*;

import java.util.ArrayList;
import java.util.Date;
import java.util.List;

@RestController
//@Controller
@RequestMapping("/restful")
@CrossOrigin(value = "http://localhost:8080",maxAge = 3600)
public class RestfulController {
    //採用RESTful風格返回資訊
    @GetMapping("/request")
//    @ResponseBody
    public String doGetRequest(){
        //回傳JSON物件
        return "{\"message\":\"返回Get查詢結果\"}";
    }

    //接收RESTful的URL參數
    //ex: Post /restful/request/100
    @PostMapping("/request/{rid}") //使用{}接收URL數值
//    @ResponseBody
    public String doPostRequest(@PathVariable(name = "rid")Integer requestId, Person person){
        System.out.println(person);
        //回傳JSON物件
        return "{\"message\":\"返回Post查詢結果\",\"id\":"+requestId+"}";
    }

    @PutMapping("/request")
//    @ResponseBody
    public String doPutRequest(Person person){
        System.out.println(person);
        return "{\"message\":\"返回Put更新結果\"}";
    }

    @DeleteMapping ("/request")
//    @ResponseBody
    public String doDeleteRequest(){
        return "{\"message\":\"返回Delete刪除結果\"}";
    }

    /**
     * 當我們使用RestController註解，並加入JSON的依賴
     * 則SpringMVC會在response時，自動將回傳值序列化成JSON的格式
     * @param id 前端查詢的輸出
     * @return Person 代會自動以JSON的格式序列化輸出
     */
    @GetMapping("/person")
    public Person findByPersonId(Integer id){
        Person p=new Person();
        if(id==1){
            p.setName("Lily");
            p.setAge(23);
        }else if(id==2){
            p.setName("Smith");
            p.setAge(22);
        }
        return p;
    }

    @GetMapping("/persons")
    public List<Person> findPersons(){
        List<Person> list=new ArrayList();

        Person p1=new Person();
        p1.setName("Lily");
        p1.setAge(23);
        p1.setBirthday(new Date());
        Person p2=new Person();
        p2.setName("Smith");
        p2.setAge(22);
        p2.setBirthday(new Date());

        list.add(p1);
        list.add(p2);
        return list;
    }
}
