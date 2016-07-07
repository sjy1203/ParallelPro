package com.company;

import org.apache.hadoop.conf.Configuration;
import org.apache.hadoop.conf.Configured;
import org.apache.hadoop.fs.FileSystem;
import org.apache.hadoop.fs.Path;
import org.apache.hadoop.io.Text;
import org.apache.hadoop.mapreduce.Job;
import org.apache.hadoop.mapreduce.lib.input.KeyValueTextInputFormat;
import org.apache.hadoop.mapreduce.lib.output.TextOutputFormat;
import org.apache.hadoop.util.Tool;

import java.io.File;

/**
 * Created by Jay on 16/7/5.
 */
public class PRDriver extends Configured implements Tool {
    @Override
    public int run(String[] strings) throws Exception {
        if (strings.length<3){
            System.err.println("parameter num < 3");
            return -1;
        }
        Job job = new Job(getConf(),"pagerank_job_"+strings[0]);
        job.setJarByClass(this.getClass());

//        Configuration configuration = job.getConfiguration();

        Path input = new Path(strings[1]);
        Path output = new Path(strings[2]);

        File file = new File(strings[2]);
        if (file.exists()){
            file.delete();
        }
//        FileSystem fileSystem = FileSystem.get(configuration);
//        if (fileSystem.exists(output)){
//            fileSystem.delete(output,true);
//        }

        KeyValueTextInputFormat.addInputPath(job,input);
        TextOutputFormat.setOutputPath(job,output);

        job.setInputFormatClass(KeyValueTextInputFormat.class);
        job.setOutputFormatClass(TextOutputFormat.class);

        job.setMapperClass(PRMapper.class);
        job.setMapOutputKeyClass(Text.class);
        job.setMapOutputValueClass(Text.class);

        job.setReducerClass(PRReducer.class);
        job.setOutputKeyClass(Text.class);
        job.setOutputValueClass(Text.class);
        return job.waitForCompletion(true)?1:0;
    }
}
