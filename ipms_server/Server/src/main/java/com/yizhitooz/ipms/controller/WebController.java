package com.yizhitooz.ipms.controller;

import com.yizhitooz.ipms.common.Result;
import org.springframework.web.bind.annotation.*;

import java.util.List;

@RestController
@RequestMapping("/web")
public class WebController {
    @RequestMapping("/hello")
    public Result hello(){
        return Result.success("Hello World");
    }

    /**
     * Post 请求，用于新增数据
     * @param o
     * @return
     */
    @PostMapping("/post")
    public Result postTest(@RequestBody ObjTest o){
        return Result.success(o);
    }

    /**
     * Put 请求，用于更新数据
     * @param o
     * @return
     */
    @PutMapping("/put")
    public Result putTest(@RequestBody ObjTest o){
        return Result.success(o);
    }

    /**
     * Delete 请求，用于删除数据
     * @param id
     * @return
     */
    @DeleteMapping("/delete/{id}")
    public Result deleteTest(@PathVariable Integer id){
        return Result.success(id);
    }

    /**
     * Delete 请求，传输JSON
     * @param ids
     * @return
     */
    @DeleteMapping("/delete/{ids}")
    public Result deleteIDsTest(@PathVariable List<Integer> ids){
        return Result.success(ids);
    }
}
