#include<iostream>
#include<bits/stdc++.h>
#include<string>
#include<vector>
#include<fstream>
#include<cmath>

using namespace std;

vector<string> OpenReading(string filename)
{
    vector<string> items;
    ifstream input(filename);
    string item;
    while(getline(input,item))
    {
        cout<<item<<endl;
        items.push_back(item);
    }

    return items;
}

class Item
{
private:
    /* data */
    string itemdetail;
    float value=0;
    float Tvalue=0;
    bool tax = true;
    bool imported=false;
    float taxvalue=0;
    float impvalue=0;
    int atpos=0;
public:
    // Item(string itemdetail){
    //     itemdetail = itemdetail;
    // };
    void Setdetail(string itemdetail){
        this->itemdetail = itemdetail;

    }
/*
    void Printdetail()
    {
        int till = atpos;
        for(int o=0;o<till;o++){
        cout<<itemdetail[o];
        }
        cout<<": ";
    }
*/
    void Parsedetail()
    {
        
        int i;
        int j;
        string counts;
       
        // used to find after product value after at keyword
        size_t at = itemdetail.find(" at ");  
        atpos = at;
        if(at!= string::npos)
        {
            j = at + 4;
        }
        
        //converting product values string to float 
        string values;
        while(j!=itemdetail.size())
        {
            values = values + itemdetail[j];
            j++;
        }

        value = stof(values);

        // check if imported or not
        if(itemdetail.find("imported") != string::npos)
        {
            imported = true;
        }
        
        // find exempted items
        string exempted[] = {"book","chocolate","pills","chocolates"}; 
        for(int k=0;k<4;k++){
            //cout<<k;
            size_t found = itemdetail.find(exempted[k]);
            if(found!=string::npos)
            {
                tax = false;
                break;
            }
        }

        Tvalue = value;
        // if tax is true
        if(tax == true){
            taxvalue = value*(0.10);
            float p = (int)(taxvalue * 100 + .5);
            taxvalue = (float)p/100;
        }

        // if imported is true
        if(imported == true)
        {
            impvalue = value*(0.05);
            float p = (int)(impvalue * 100 + 0.5);
            impvalue = (float)p/100;
            
        }
        Tvalue = Tvalue + taxvalue+impvalue;

        int till = atpos;
        for(int o=0;o<till;o++){
        cout<<itemdetail[o];
        }
        cout<<": "<<Tvalue<<endl;;
        
    }
    
    float getTaxvalue(){
        return taxvalue+impvalue;
    }

    float getTotalvalue()
    {
        return Tvalue;
    }

};

// rounding off to neares 0.05 function
float Roundoff(float V)
{
    float x = V*10;
    int y = (int) x;
    float z = x - (float) y;
    z = z*10;
    if(z>5){
        if(z>7)
        {
            z = 10;
        }
        else{
            z = 5;
        }
    }
    else{
        if(z>2)
        {
            z = 5;
        }
        else{
            z = 0;
        }
    }

    y = y*10 + z;
    return((float)y/100);
}


int main()
{
    string filename = "input3.txt"; //input1.txt and input2.txt 
    vector<string> items;
    items = OpenReading(filename);
    cout<<endl;
    int totalitem = items.size();
    Item itm[totalitem];
    float totaltax=0;
    float totalallvalue=0;

    for(int i = 0; i < items.size(); i++)
	{
        itm[i].Setdetail(items[i]);
        itm[i].Parsedetail();
        //itm[i].Printdetail();
        //cout<<fixed<<setprecision(2)<<Roundoff(itm[i].getTotalvalue())<<endl;
        totaltax = totaltax + itm[i].getTaxvalue();
        totalallvalue = totalallvalue + itm[i].getTotalvalue();
    }
    cout<<fixed<<setprecision(2)<<"Sales Taxes: "<<Roundoff(totaltax)<<endl;
    cout<<fixed<<setprecision(2)<<"Total: "<<totalallvalue<<endl;

    return 0;
}
