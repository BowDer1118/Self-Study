package com.imooc.mybatis;

import com.github.pagehelper.Page;
import com.github.pagehelper.PageHelper;
import com.imooc.mybatis.dto.GoodsDTO;
import com.imooc.mybatis.entity.Goods;
import com.imooc.mybatis.entity.GoodsDetail;
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
import java.util.*;

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

    //測試1級Cache
    @Test
    public void testLv1Cache(){
        SqlSession sqlSession=null;
        try{
            sqlSession=MyBatisUtils.openSession();
            Integer value=new Integer(1603);
            //使用selectOne獲取一筆資料 並將要傳入的參數傳給函數
            Goods good=sqlSession.selectOne("goods.selectById",value);
            Goods good2=sqlSession.selectOne("goods.selectById",value);
            //相同的查詢結果會指向JVM記憶體中的同個物件
            System.out.println(good.hashCode()+":"+good2.hashCode());
        }catch (Exception e){
            e.printStackTrace();
        }finally {
            MyBatisUtils.closeSession(sqlSession);
        }

        sqlSession=null;
        try{
            sqlSession=MyBatisUtils.openSession();
            Integer value=new Integer(1603);
            //使用selectOne獲取一筆資料 並將要傳入的參數傳給函數
            Goods good=sqlSession.selectOne("goods.selectById",value);
            //使用commit時會強制清空該namespace的Cache
            sqlSession.commit();
            Goods good2=sqlSession.selectOne("goods.selectById",value);
            System.out.println(good.hashCode()+":"+good2.hashCode());
        }catch (Exception e){
            e.printStackTrace();
        }finally {
            MyBatisUtils.closeSession(sqlSession);
        }
    }

    //測試2級Cache
    @Test
    public void testLv2Cache(){
        SqlSession sqlSession=null;
        try{
            sqlSession=MyBatisUtils.openSession();
            Integer value=new Integer(1603);
            //使用selectOne獲取一筆資料 並將要傳入的參數傳給函數
            Goods good=sqlSession.selectOne("goods.selectById",value);
            //相同的查詢結果會指向JVM記憶體中的同個物件
            System.out.println(good.hashCode());
        }catch (Exception e){
            e.printStackTrace();
        }finally {
            MyBatisUtils.closeSession(sqlSession);
        }

        sqlSession=null;
        try{
            sqlSession=MyBatisUtils.openSession();
            Integer value=new Integer(1603);
            //使用selectOne獲取一筆資料 並將要傳入的參數傳給函數
            Goods good=sqlSession.selectOne("goods.selectById",value);
            //使用commit時會強制清空該namespace的Cache
            System.out.println(good.hashCode());
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
    public void testInsert(){
        SqlSession sqlSession=null;
        try{
            sqlSession=MyBatisUtils.openSession();
            Goods goods=new Goods();
            goods.setTitle("測試插入功能");
            goods.setSubtitle("測試插入功能的資料");
            goods.setOriginalCost(200f);
            goods.setCurrentPrice(100f);
            goods.setDiscount(0.5f);
            goods.setIsFreeDelivery(1);
            goods.setCategoryId(43);
            //將Goods物件插入到資料庫
            //返回值為成功插入的紀錄總數
            int num=sqlSession.insert("goods.insert",goods);
            //使用commit將insert的資料都寫入資料庫
            sqlSession.commit();
            System.out.println(goods.getGoodsId());
        }catch (Exception e){
            if(sqlSession!=null){
                //使用rollback回滾插入操作
                sqlSession.rollback();
            }
            e.printStackTrace();
        }finally {
            MyBatisUtils.closeSession(sqlSession);
        }
    }

    @Test
    public void testUpdate(){
        SqlSession sqlSession=null;
        try{
            sqlSession=MyBatisUtils.openSession();
            //先執行搜尋並更資料
            Goods goods=sqlSession.selectOne("goods.selectById",739);
            goods.setTitle("更新測試商品");
            //更新資料庫資料 返回值為本次更新的數量
            int num=sqlSession.update("goods.update",goods);
            //執行更新
            sqlSession.commit();
            goods=sqlSession.selectOne("goods.selectById",739);
            System.out.println(goods);
        }catch (Exception e){
            e.printStackTrace();
        }finally {
            MyBatisUtils.closeSession(sqlSession);
        }
    }

    @Test
    public void testDelete(){
        SqlSession sqlSession=null;
        try{
            sqlSession=MyBatisUtils.openSession();
            //使用主Key:goodsId來當作要刪除的索引 返回值為總共刪除的資料數量
            int num=sqlSession.update("goods.delete",739);
            sqlSession.commit();
        }catch (Exception e){
            e.printStackTrace();
        }finally {
            MyBatisUtils.closeSession(sqlSession);
        }
    }

    @Test
    public void testDynamicSQL(){
        SqlSession sqlSession=null;
        try{
            sqlSession=MyBatisUtils.openSession();
            Map parm=new HashMap();
            parm.put("categoryId",44);
            parm.put("currentPrice",500);
            List<Goods> list=sqlSession.selectList("goods.dynamicSQL",parm);
            for(Goods g:list){
                System.out.println(g.getTitle()+":"+g.getCategoryId()+":"+g.getCurrentPrice());
            }
        }catch (Exception e){
            e.printStackTrace();
        }finally {
            MyBatisUtils.closeSession(sqlSession);
        }
    }

    @Test
    public void testOneToMany(){
        SqlSession sqlSession=null;
        try{
            sqlSession=MyBatisUtils.openSession();
            List<Goods> list=sqlSession.selectList("goods.selectOneToMany");
            for(Goods goods:list){
                System.out.println(goods.getTitle()+":"+goods.getGoodsDetails().size());
            }
        }catch (Exception e){
            e.printStackTrace();
        }finally {
            MyBatisUtils.closeSession(sqlSession);
        }
    }

    @Test
    public void testManyToOne(){
        SqlSession sqlSession=null;
        try{
            sqlSession=MyBatisUtils.openSession();
            List<GoodsDetail> list=sqlSession.selectList("goodsDetail.selectManyToOne");
            for(GoodsDetail g:list){
                System.out.println(g);
            }
        }catch (Exception e){
            e.printStackTrace();
        }finally {
            MyBatisUtils.closeSession(sqlSession);
        }
    }

    @Test
    public void testSelectPage(){
        SqlSession sqlSession=null;
        try{
            sqlSession=MyBatisUtils.openSession();
            //使用PageHelper查詢特定頁面(傳入當前想要去的頁數,每頁幾筆資料)
            PageHelper.startPage(2,10);
            //將查詢到的List集合轉換成Page物件
            Page<Goods> page=(Page)sqlSession.selectList("goods.selectPage");
            System.out.println("總頁數:"+page.getPages());
            System.out.println("總紀錄數:"+page.getTotal());
            System.out.println("開始行號:"+page.getStartRow());
            System.out.println("結束行號:"+page.getEndRow());
            System.out.println("當前頁碼:"+page.getPageNum());
            List<Goods> data=page.getResult();
            for(Goods g:data){
                System.out.println(g.getTitle());
            }
        }catch (Exception e){
            e.printStackTrace();
        }finally {
            MyBatisUtils.closeSession(sqlSession);
        }
    }

    @Test
    public void testBatchInsert(){
        SqlSession sqlSession=null;
        try{
            sqlSession=MyBatisUtils.openSession();
            long st=new Date().getTime();
            //產生10000筆資料
            List list=new ArrayList();
            for(int i=0;i<10000;i++){
                Goods goods=new Goods();
                goods.setTitle("測試商品");
                goods.setSubtitle("測試子標題");
                goods.setOriginalCost(200f);
                goods.setCurrentPrice(100f);
                goods.setDiscount(0.5f);
                goods.setIsFreeDelivery(1);
                goods.setCategoryId(43);
                list.add(goods);
            }
            sqlSession.insert("goods.batchInsert",list);
            sqlSession.commit();
            long et=new Date().getTime();
            System.out.println("執行時間"+(et-st)+"毫秒");
        }catch (Exception e){
            e.printStackTrace();
            sqlSession.rollback();
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
        }finally {
            MyBatisUtils.closeSession(sqlSession);
        }
    }

    @Test
    public void testStudentInsert(){
        SqlSession sqlSession=null;
        try{
            sqlSession=MyBatisUtils.openSession();
           Student student=new Student();
           student.setRegNo(20171208);
           student.setName("言豫津");
           student.setSex("男");
           student.setAge(26);
           student.setGrade("2013");
           student.setMajor("哲學系");
            //返回值為成功插入的紀錄總數
            int num=sqlSession.insert("student.insert",student);
            System.out.printf("Insert %d data into database\n",num);
            //使用commit將insert的資料都寫入資料庫
            sqlSession.commit();
            System.out.println(student);
        }catch (Exception e){
            if(sqlSession!=null){
                //使用rollback回滾插入操作
                sqlSession.rollback();
            }
            e.printStackTrace();
        }finally {
            MyBatisUtils.closeSession(sqlSession);
        }
    }

    @Test
    public void testStudentDynamicSQL(){
        SqlSession sqlSession=null;
        try{
            sqlSession=MyBatisUtils.openSession();
            Map parm=new HashMap();
            List<Student> studentList=sqlSession.selectList("student.dynamicSQL",parm);
            System.out.printf("所有學生訊息:共%d位學生\n",studentList.size());
            for(Student s:studentList){
                System.out.println(s);
            }
            parm.put("age",30);
            studentList=sqlSession.selectList("student.dynamicSQL",parm);
            System.out.printf("年齡大於30歲:共%d位學生\n",studentList.size());
            for(Student s:studentList){
                System.out.println(s);
            }
            parm.put("sex","男");
            studentList=sqlSession.selectList("student.dynamicSQL",parm);
            System.out.printf("年齡大於30歲並且性別為男生:共%d位學生\n",studentList.size());
            for(Student s:studentList){
                System.out.println(s);
            }
        }catch (Exception e){
            e.printStackTrace();
        }finally {
            MyBatisUtils.closeSession(sqlSession);
        }
    }
}
