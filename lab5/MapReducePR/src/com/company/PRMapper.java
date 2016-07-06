package com.company;


import org.apache.hadoop.io.Text;
import org.apache.hadoop.mapreduce.Mapper;

import java.io.IOException;
import java.util.logging.Logger;

/**
 * Created by Jay on 16/7/5.
 */
public class PRMapper extends Mapper<Text,Text,Text,Text>{
    private static final Logger logger = Logger.getLogger("PRMapper");

    public static float init = 0.4f;
    @Override
    protected void map(Text key, Text value, Context context) throws IOException, InterruptedException {
        logger.info(key.toString()+";"+value.toString());

        String[] outLinks = value.toString().split(",");
        String[] link = key.toString().split(",");
        float rank = init;
        if (link.length>1){
            rank = Float.parseFloat(link[1]);
        }
        int outLinkLen = outLinks.length;
        for (String s: outLinks){
            context.write(new Text(s),new Text(link[0]+";"+rank/outLinkLen));
        }
        context.write(new Text(link[0]),value);
    }
}
