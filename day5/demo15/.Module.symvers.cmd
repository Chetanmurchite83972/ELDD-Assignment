cmd_/home/chetan/ELDD/day5/demo15/Module.symvers :=  sed 's/ko$$/o/'  /home/chetan/ELDD/day5/demo15/modules.order | scripts/mod/modpost -m -a    -o /home/chetan/ELDD/day5/demo15/Module.symvers -e -i Module.symvers -T - 