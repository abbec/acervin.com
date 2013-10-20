require 'nanoc3/tasks'

task :deploy do
    puts %x[rsync -avzh --progress --delete --rsh='ssh -p 2223' output/ abbe@megatron.ragingmoon.se:/srv/httpd/acervin/]
end
