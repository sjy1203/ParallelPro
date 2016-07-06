package com.company;

import org.apache.hadoop.io.Text;
import org.apache.hadoop.mapreduce.Reducer;

import java.io.IOException;
import java.util.logging.Logger;

/**
 * Created by Jay on 16/7/5.
 */
public class PRReducer extends Reducer<Text,Text,Text,Text> {
    private static final Logger logger = Logger.getLogger("PRReducer");

    @Override
    protected void reduce(Text key, Iterable<Text> values, Context context) throws IOException, InterruptedException {
        logger.info(key.toString());
        float rank= 0f;
        String[] str;
        Text outLinks = new Text();
        for (Text t: values){
            str = t.toString().split(";");
            if (str.length==2){
                rank+=Float.parseFloat(str[1]);
            }else{
                outLinks.set(t.toString());
            }
        }
        context.write(new Text(key.toString()+","+rank),outLinks);
    }
}
