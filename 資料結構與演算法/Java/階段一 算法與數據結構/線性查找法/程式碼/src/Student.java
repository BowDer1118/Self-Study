
public class Student {
    private String name;

    public Student(String name) {
        this.name = name;
    }

    @Override
    public boolean equals(Object student) {
        //如果參考位置相同--->同一個物件
        if(this==student){
            return true;
        }

        if(student==null){
            return false;
        }

        //類別轉換檢查
        if(this.getClass()!=student.getClass()){
            return false;
        }

        Student another=(Student)student;
        return this.name.equalsIgnoreCase(another.name);
    }
}
