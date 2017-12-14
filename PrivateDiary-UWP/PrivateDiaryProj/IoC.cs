using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Autofac;
using PrivateDiary.Service;

namespace PrivateDiary
{
    public static class IoC
    {
        public static IContainer Container { get; set; }

        static IoC()
        {
            var builder = new ContainerBuilder();
            builder.RegisterType<DataContext>().As<IDataContext>();
            builder.RegisterType<UserService>().As<IUserService>();

            Container = builder.Build();
        }
    }
}
