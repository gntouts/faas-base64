FROM gntouts/musl-gcc:latest as builder

WORKDIR /workspace
COPY ./ .
RUN make clean
RUN make local && mv faas-base64 /sbin/faas-base64

FROM busybox:latest
EXPOSE 8000
COPY --from=builder /sbin/faas-base64 /sbin/faas-base64
CMD [ "/sbin/faas-base64", "8000" ]