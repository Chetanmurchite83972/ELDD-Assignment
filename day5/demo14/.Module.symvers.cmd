cmd_/home/chetan/ELDD/day5/demo14/Module.symvers :=  sed 's/ko$$/o/'  /home/chetan/ELDD/day5/demo14/modules.order | scripts/mod/modpost -m -a    -o /home/chetan/ELDD/day5/demo14/Module.symvers -e -i Module.symvers -T - 
