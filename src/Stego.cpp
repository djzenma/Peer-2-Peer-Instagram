#include "../headers/Stego.h"
#include <iostream>

//reading size of image file
int size_of_image(FILE *fp1)
{
    int size;
    fseek(fp1, 0, SEEK_END);
    size = ftell(fp1);
    fseek(fp1, 0, SEEK_SET);
    printf("Size of the Image is %d \n", size);
    fseek(fp1, 0L, SEEK_SET);	//Seek to the start position

    return size;
}

//bits of text file
int get_bit(char byte, int bit)
{
    return ((byte >> 8 - bit) & 1);
}

//encription of message
void stega_encrypt(FILE *fp1, char * secret_buff, FILE *fp3)
{
    char file_buff = 0, msg_buff = 0, ch;	//temp var for one byte from file and msg
    int i;
    int bit_msg;
    int indx = 0;
    while((msg_buff = secret_buff[indx++]) != '\0')
    {
        for(i = 1; i <= 8; i++)
        {
            file_buff = fgetc(fp1);

            int file_byte_lsb = (file_buff & 1);

            bit_msg = get_bit(msg_buff, i);

            if(file_byte_lsb == bit_msg)
            {
                fputc(file_buff, fp3);
            }
            else
            {
                if(file_byte_lsb == 0)
                    file_buff = (file_buff | 1);
                else
                    file_buff = (file_buff ^ 1);

                fputc(file_buff, fp3);
            }
        }
    }

    /*copying rest of data */
    while(!feof(fp1))
    {
        char tmp_cpy = fgetc(fp1);
        fputc(tmp_cpy,fp3);

    }

    if(msg_buff == '\0')
        printf("\n*** Secret Message Encrypted Successfully ***\n");
    else
        printf("\n*** Failed Encrypting ***\n");
}
//Encription For Strings
void string_encrypt(char *str,FILE *fp1, FILE *fp3)
{

    char file_buff, msg_buff;	//temp var for one byte from file and msg
    int i, j = 0;
    int bit_msg;
    while((msg_buff = str[j]) != '\0')
    {
        for(i = 1; i <= 8; i++)
        {
            file_buff = fgetc(fp1);

            int file_byte_lsb = (file_buff & 1);

            bit_msg = get_bit(msg_buff, i);

            if(file_byte_lsb == bit_msg)
            {
                fputc(file_buff, fp3);
            }
            else
            {
                if(file_byte_lsb == 0)
                    file_buff = (file_buff | 1);
                else
                    file_buff = (file_buff ^ 1);

                fputc(file_buff, fp3);
            }
        }
        j++;
    }
}
//Encription For Numbers
void size_encrypt(int num,FILE *fp1, FILE *fp3)
{

    char file_buff;
    int i, j = 0;
    int bit_msg;

    for(i = 1; i <= 8; i++)
    {
        file_buff = fgetc(fp1);

        int file_byte_lsb = (file_buff & 1);

        bit_msg = get_bit(num, i);

        if(file_byte_lsb == bit_msg)
        {
            fputc(file_buff, fp3);
        }
        else
        {
            if(file_byte_lsb == 0)
                file_buff = (file_buff | 1);
            else
                file_buff = (file_buff ^ 1);

            fputc(file_buff, fp3);
        }
    }

}

std::string stega_encode(std::string image_file ,std::string secret_msg, std::string stego_image)
{
    FILE *fp1, *fp3;

    //opening Image File
    if((fp1 = fopen(image_file.c_str(), "r+")) == NULL)
    {
        printf("Could not open file %s.\nAborting\n", image_file.c_str());
        exit(1);
    }

    int size_image = size_of_image(fp1);
    printf("Total %d Charecters can be stored in %s.\n", size_image, image_file.c_str());

    int size_txt = secret_msg.length();
    printf("\nSize of The Secret Message is ==> %d\n", size_txt);

    //Comparing Image Size With Text
    if(size_image < size_txt)
    {
        printf("\n*** The Size Of Message Exceeds the Size of image ***\n");
        exit(1);
    }

    //opening destination file
    fp3 = fopen(stego_image.c_str(), "w+");
    if (fp3== NULL)
    {
        fprintf(stderr, "Cannot create output file %s\n",stego_image.c_str());
        exit(1);
    }

    //copying 54 header file
    int i, c = 0;
    char tmp_cpy;
    rewind(fp1);	//Goes back to the beginning of the file
    for(i = 0;i < 54; i++)
    {
        tmp_cpy = fgetc(fp1);
        fputc(tmp_cpy,fp3);
        c++;
    }

    //checking 54 bytes copyed or not
    if(i == c)
        printf("\n*** Sucessfully copied 54 header bytes ***\n");
    else
    {
        printf("\n*** Failed to copy 54 header bytes ***\n");
        exit(0);
    }


    //Encryption for Message
    size_encrypt(size_txt,fp1,fp3);
    stega_encrypt(fp1,(char *)secret_msg.c_str(),fp3);

    /*Clean up before exit */
    fclose(fp1);
    fclose(fp3);

    std::ifstream ifs(stego_image, std::ios::in | std::ios::binary); // input file
    std::ostringstream oss; // output to string

    int len;
    char buf[1024];
    while((len = ifs.readsome(buf, 1024)) > 0)
    {
        oss.write(buf, len);
    }

    std::string data = oss.str(); // get string data out of stream

    return data;
}

/* decryption of sizes */
void size_decryption(FILE *pf1, int *size_txt)
{
    int file_buff = 0, i;
    int ch, bit_msg;
    for (i = 0; i < 8; i++)
    {
        ch = fgetc(pf1);
        bit_msg = (ch & 1);
        if (bit_msg)
        {
            file_buff = (file_buff << 1) | 1;
        }
        else
        {
            file_buff = file_buff << 1;
        }
    }
    *size_txt = file_buff;
}

/* decryption of strings*/
void string_decryption(FILE *pf1,char *strng,int size)
{
    int file_buff=0, i, j=0, k=0;
    int ch, bit_msg;
    for (i = 0; i < (size * 8); i++)
    {
        j++;
        ch = fgetc(pf1);
        bit_msg = (ch & 1);
        if (bit_msg)
        {
            file_buff = (file_buff << 1) | 1;
        }
        else
        {
            file_buff = file_buff << 1;
        }

        if ( j == 8)
        {
            strng[k] =(char)file_buff;
            j=0;
            k++;
            file_buff = 0;
        }
    }
    strng[k] = '\0';
}


/* decryption of secret message*/
std::string secret_decryption(int size_txt, FILE *pf1)
{
    int file_buff=0, i, j = 0, k = 0;
    int ch,bit_msg;
    char output[250] = {0};
    std::cout << "size: " << size_txt << std::endl;

    for (i = 0; i < (size_txt * 8); i++)
    {
        j++;
        ch = fgetc(pf1);
        bit_msg = (ch & 1);
        if (bit_msg)
        {
            file_buff = (file_buff << 1) | 1;
        }
        else
        {
            file_buff = file_buff << 1;
        }

        if ( j == 8)
        {
            output[k++] = file_buff;
            j=0;
            file_buff = 0;
        }
    }
    printf("\n*** Secret Text Is ==> %s\n\n", output);
    return std::string(output);
}


std::string stega_decode(std::string stego_image)
{
    FILE *pf1;

    int size_txt;

    //opening Image File
    if((pf1 = fopen(stego_image.c_str(), "r")) == NULL)
    {
        printf("Could not open file %s.\nAborting\n", stego_image.c_str());
        exit(1);
    }

    fseek(pf1,54 ,SEEK_SET);

    /*Secret Text */
    size_decryption(pf1, &size_txt);
    std::string output = secret_decryption(size_txt, pf1);

    /* closeing files */
    fclose(pf1);

    return output;
}