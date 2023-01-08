package com.imooc.mybatis;

import com.imooc.mybatis.dto.GoodsDTO;
import com.imooc.mybatis.entity.Goods;
import com.imooc.mybatis.entity.Student;
import com.imooc.mybatis.utils.MyBatisUtils;
import org.apache.ibatis.io.Resources;
import org.apache.ibatis.session.SqlSession;
import org.apache.ibatis.session.SqlSessionFactory;
import org.apache.ibatis.session.SqlSessionFactoryBuilder;
import org.junit.Test;

import java.io.IOException;
import java.io.Reader;
import java.sql.Connection;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

/*測試MyBatis框架*/
public class MyBatisTestor {
    @Test
    public void testSqlSessionFactory(){
        try {
            //使用Reader加載mybatis-config.xml(默認從resources資料夾下加載設定檔案)
            Reader reader=Resources.getResourceAsReader("mybatis-config.xml");
            //使用SqlSessionFactoryBuilder().build()傳入並解析reader物件，就能獲取SqlSessionFactory物件了
            SqlSessionFactory sqlSessionFactory=new SqlSessionFactoryBuilder().build(reader);
            System.out.println("SessionFactory加載成功");
            /*到目前為止，只是完成解析config檔案並初始化mybaits框架，尚未與資料庫連線*/

            //創建SqlSession物件，該物件為JDBC的擴展類用於與資料庫交互
            SqlSession sqlSession=null;

            //嘗試連線
            try {
                sqlSession=sqlSessionFactory.openSession();
                //測試用:使用Connection對資料庫進行連結(失敗會拋出異常)
                Connection connection=sqlSession.getConnection();
                System.out.println(connection);
            }catch (Exception e){
                e.printStackTrace();
            }finally {
                //如果成功連線 要斷開連線
                if(sqlSession!=null){
                    sqlSession.close();
                }
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    @Test
    public void testMyBatisUtils(){
        SqlSession sqlSession= null;
        try{
            sqlSession=MyBatisUtils.openSession();
            if(sqlSession!=null){
                System.out.println("成功獲得SqlSession");
                Connection connection=sqlSession.getConnection();
                System.out.println(connection);
            }
        }catch (Exception e){
            throw e;
        }finally {
            MyBatisUtils.closeSession(sqlSession);
        }
    }

    @Test
    public void testSelectAll(){
        SqlSession sqlSession=null;
        try{
            sqlSession=MyBatisUtils.openSession();
            //使用selectList獲取多比查詢資料，需傳入:namespace.id字串 來表示要執行的查詢語句
            List<Goods> goodsList=sqlSession.selectList("goods.selectAll");
            for(Goods g:goodsList){
                System.out.println(g.getTitle());
            }
        }catch (Exception e){
            e.printStackTrace();
        }finally {
            MyBatisUtils.closeSession(sqlSession);
        }
    }

    @Test
    public void testSelectById(){
        SqlSession sqlSession=null;
        try{
            sqlSession=MyBatisUtils.openSession();
            Integer value=new Integer(1603);
            //使用selectOne獲取一筆資料 並將要傳入的參數傳給函數
            Goods good=sqlSession.selectOne("goods.selectById",value);
            System.out.println(good);
        }catch (Exception e){
            e.printStackTrace();
        }finally {
            MyBatisUtils.closeSession(sqlSession);
        }
    }

    @Test
    public void testSelectByPriceRange(){
        SqlSession sqlSession=null;
        try{
            sqlSession=MyBatisUtils.openSession();

            Map<String,Integer> param=new HashMap();
            param.put("min",100);
            param.put("max",500);
            param.put("limt",10);

            //使用Map傳入多個參數
            List<Goods> goodsList=sqlSession.selectList("goods.selectByPriceRange",param);
            for (Goods g: goodsList) {
                System.out.println(g.getCurrentPrice());
            }
        }catch (Exception e){
            e.printStackTrace();
        }finally {
            MyBatisUtils.closeSession(sqlSession);
        }
    }

    @Test
    public void testSelectGoodsMap(){
        SqlSession sqlSession=null;
        try{
            sqlSession=MyBatisUtils.openSession();
            List<Map> list=sqlSession.selectList("goods.selectGoodsMap");
            for(Map m:list){
                //Key的資料型態為String代表資料庫中表的欄位名稱,每個value的資料型態會依照資料庫儲存的資料類型而有不同
                System.out.println(m);
            }
        }catch (Exception e){
            e.printStackTrace();
        }finally {
            MyBatisUtils.closeSession(sqlSession);
        }
    }

    @Test
    public void testSelectGoodsDTO(){
        SqlSession sqlSession=null;
        try{
            sqlSession=MyBatisUtils.openSession();
            List<GoodsDTO> goodsDTOList=sqlSession.selectList("goods.selectGoodsDTO");
            for(GoodsDTO g:goodsDTOList){
                System.out.println(g.getGoods().getTitle());
            }
        }catch (Exception e){
            e.printStackTrace();
        }finally {
            MyBatisUtils.closeSession(sqlSession);
        }
    }
    @Test
    public void testStudentSelectionAll(){
        SqlSession sqlSession=null;
        try{
            sqlSession=MyBatisUtils.openSession();
            List<Student> studentList=sqlSession.selectList("student.selectAll");
            for(Student s:studentList){
                System.out.println(s);
            }
        }catch (Exception e){
            e.printStackTrace();
        }
    }
}
