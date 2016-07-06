package com.company;

import org.apache.hadoop.conf.Configuration;
import org.apache.hadoop.util.ToolRunner;

public class Main {

    public static void main(String[] args) throws Exception {
	// write your code here
        if (args.length<3){
            System.err.println("main args number < 3");
            System.exit(-1);
        }
        int count = Integer.parseInt(args[0]);
        String input = args[1];
        String output = args[2];
        String temp = "";
        int res;
        Configuration configuration = new Configuration();

        PRDriver driver;
        for (int i=0;i<count;i++){
            driver = new PRDriver();
            driver.setConf(configuration);
            res = ToolRunner.run(driver,new String[]{String.valueOf(i),input,output});
            if (res>0){
                temp = input;
                input = output;
                output = temp;
                System.out.println("job_"+i+" success");
            }else{
                System.out.println("job_"+i+" failed");
            }

        }
    }
}
